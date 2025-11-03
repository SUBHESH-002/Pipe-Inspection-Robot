/*
 * Active-Omni PipeBot — Main Controller
 * Two wheel modules, each with:
 *   - Hub motor (omega_h1, omega_h2)
 *   - Central bevel motor (omega_c1, omega_c2)
 * Rack actuator sets wall-contact preload N via PID.
 *
 * Body-frame commands: vx [m/s], vy [m/s], wz [rad/s]
 * Kinematics per docs/Kinematics_Derivation.md
 */

#include "inverse_kinematics.h"

// ================== USER TUNABLES ==================
static const float Rh     = 0.025f;    // hub radius [m]
static const float rr     = 0.008f;    // roller radius [m]
static const float alpha  = 45.0f;     // roller axle angle [deg]
static const float G      = 1.50f;     // central:roller gear ratio
static const float B      = 0.10f;     // track (wheel-center spacing) [m]
static const float kappa  = G * rr * cosf(alpha * 3.14159265f/180.0f);

// Motor/driver setup (example TB6612FNG-style pins; adjust to your wiring)
#define H1_PWM 5
#define H1_IN1 7
#define H1_IN2 8
#define H2_PWM 6
#define H2_IN1 9
#define H2_IN2 10

#define C1_PWM 3
#define C1_IN1 11
#define C1_IN2 12
#define C2_PWM 4
#define C2_IN1 A2
#define C2_IN2 A3

// Rack actuator (DC motor or servo). Here: DC with H-bridge
#define R_PWM  2
#define R_IN1  A0
#define R_IN2  A1

// Encoder pins (placeholders if you have them)
#define ENC_H1_A 18
#define ENC_H1_B 19
#define ENC_H2_A 20
#define ENC_H2_B 21
#define ENC_C1_A 22
#define ENC_C1_B 23
#define ENC_C2_A 24
#define ENC_C2_B 25

// Control loop timing
static const float CTRL_HZ = 100.0f;
static const float DT      = 1.0f/CTRL_HZ;

// Preload (rack) control targets (Stage 2 numbers -> refine later)
static const float m_robot   = 3.5f;    // [kg] update after weigh-in
static const float mu        = 0.6f;    // friction wheel/pipe
static const float g_const   = 9.81f;
static const float sf_pre    = 1.4f;    // safety factor for preload

// Rack PID gains (start conservative; tune on bench)
static const float KP_R = 0.8f;
static const float KI_R = 0.3f;
static const float KD_R = 0.0f;

// ========= Simple IO helpers =========
static inline void motorDrive(int pwmPin, int in1, int in2, float cmd) {
  // cmd in [-1, 1]; map to direction + PWM (0..255)
  int pwm = (int)(min(1.0f, max(-1.0f, cmd)) * 255.0f);
  if (pwm >= 0) {
    digitalWrite(in1, HIGH); digitalWrite(in2, LOW);
    analogWrite(pwmPin, pwm);
  } else {
    digitalWrite(in1, LOW);  digitalWrite(in2, HIGH);
    analogWrite(pwmPin, -pwm);
  }
}

static inline float rpmToCmd(float target_rpm, float max_rpm) {
  // Linear map RPM → normalized command [-1..1]
  if (max_rpm <= 1e-6f) return 0.0f;
  float u = target_rpm / max_rpm;
  if (u > 1.0f) u = 1.0f;
  if (u < -1.0f) u = -1.0f;
  return u;
}

// ======== Rack preload “sensor” placeholder ========
// Option 1: use inline load cell → return N per side.
// Option 2: control via rack position & characterize N(pos) offline.
// For now: emulate “measured preload” with a dummy variable you can overwrite.
float rack_measured_N = 0.0f;      // [N], update with real sensing later
float rack_integral   = 0.0f;

// ======== Motion command (can be replaced by UART/ROS later) ========
volatile float cmd_vx = 0.00f;   // [m/s]
volatile float cmd_vy = 0.00f;   // [m/s]
volatile float cmd_wz = 0.00f;   // [rad/s]

// Limits for conversion to RPM (set by your motors/gearbox)
static const float HUB_MAX_RPM = 180.0f;   // example: 180 rpm after gearbox
static const float CEN_MAX_RPM = 300.0f;

void setup() {
  pinMode(H1_PWM, OUTPUT); pinMode(H1_IN1, OUTPUT); pinMode(H1_IN2, OUTPUT);
  pinMode(H2_PWM, OUTPUT); pinMode(H2_IN1, OUTPUT); pinMode(H2_IN2, OUTPUT);
  pinMode(C1_PWM, OUTPUT); pinMode(C1_IN1, OUTPUT); pinMode(C1_IN2, OUTPUT);
  pinMode(C2_PWM, OUTPUT); pinMode(C2_IN1, OUTPUT); pinMode(C2_IN2, OUTPUT);
  pinMode(R_PWM,  OUTPUT); pinMode(R_IN1,  OUTPUT); pinMode(R_IN2,  OUTPUT);

  // If using encoders/IMU, init here

  // Example: set a gentle helical command initially
  cmd_vx = 0.05f;   // 5 cm/s forward
  cmd_vy = 0.00f;   // no lateral
  cmd_wz = 0.00f;   // no yaw

  // Serial for command updates
  Serial.begin(115200);
}

void loop() {
  static unsigned long t_prev = millis();
  unsigned long t_now = millis();
  if (t_now - t_prev < (unsigned long)(1000.0f/CTRL_HZ)) return;
  t_prev = t_now;

  // ---- 1) Inverse Kinematics ----
  float oh1, oh2, oc1, oc2; // rad/s
  invKin_twoWheel(vx_from(cmd_vx), vy_from(cmd_vy), cmd_wz,
                  Rh, kappa, B, oh1, oh2, oc1, oc2);

  // Convert rad/s → RPM
  float h1_rpm = (oh1 * 60.0f) / (2.0f * 3.14159265f);
  float h2_rpm = (oh2 * 60.0f) / (2.0f * 3.14159265f);
  float c1_rpm = (oc1 * 60.0f) / (2.0f * 3.14159265f);
  float c2_rpm = (oc2 * 60.0f) / (2.0f * 3.14159265f);

  // ---- 2) Convert RPM → normalized command [-1..1] ----
  float u_h1 = rpmToCmd(h1_rpm, HUB_MAX_RPM);
  float u_h2 = rpmToCmd(h2_rpm, HUB_MAX_RPM);
  float u_c1 = rpmToCmd(c1_rpm, CEN_MAX_RPM);
  float u_c2 = rpmToCmd(c2_rpm, CEN_MAX_RPM);

  // ---- 3) Rack preload PID (per side combined) ----
  float N_target = sf_pre * (m_robot * g_const) / (2.0f * mu); // per wheel
  float eN = (N_target) - rack_measured_N;  // if you sense per side, run two PIDs
  rack_integral += eN * DT;
  float rack_u = KP_R*eN + KI_R*rack_integral; // + KD_R*(de/dt) if you add derivative
  // Bound command
  if (rack_u > 1.0f) rack_u = 1.0f;
  if (rack_u < -1.0f) rack_u = -1.0f;

  // ---- 4) Drive outputs ----
  motorDrive(H1_PWM, H1_IN1, H1_IN2, u_h1);
  motorDrive(H2_PWM, H2_IN1, H2_IN2, u_h2);
  motorDrive(C1_PWM, C1_IN1, C1_IN2, u_c1);
  motorDrive(C2_PWM, C2_IN1, C2_IN2, u_c2);
  motorDrive(R_PWM,  R_IN1,  R_IN2,  rack_u);

  // ---- 5) Optional: serial command injection ----
  // Expected format: vx vy wz (in SI), e.g., "0.05 0.00 0.0\n"
  if (Serial.available()) {
    float vx, vy, wz;
    if (3 == Serial.readBytesUntil('\n', nullptr, 0)) { /* placeholder */ }
    // For simplicity, send "VX VY WZ\n" and parse with Serial.parseFloat()
    vx = Serial.parseFloat(); vy = Serial.parseFloat(); wz = Serial.parseFloat();
    if (Serial.read() == '\n') { cmd_vx=vx; cmd_vy=vy; cmd_wz=wz; }
  }
}

// Helpers to keep vx, vy within reasonable range:
static inline float vx_from(float v){ return constrain(v, -0.20f, +0.20f); } // ±0.2 m/s
static inline float vy_from(float v){ return constrain(v, -0.15f, +0.15f); } // ±0.15 m/s
