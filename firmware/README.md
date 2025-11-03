# 🧠 Firmware — Active Omni PipeBot

This firmware drives **two active-omni wheel modules** (each with a hub motor + central bevel motor) and a **rack actuator** for wall-contact preload, using the inverse kinematics defined in `/docs/Kinematics_Derivation.md`.

## 📂 Files
- `main_controller/main.ino` — main loop, motor outputs, rack preload PID, serial command parsing
- `main_controller/inverse_kinematics.h` — closed-form IK for (vx, vy, ωz) → (ωh1, ωh2, ωc1, ωc2)

---

## 🛠 Build & Flash
- Board: *Arduino Mega / UNO / ESP32* (pick one and adjust pins)
- IDE: Arduino IDE or PlatformIO
- Dependencies: none (standard `Arduino.h`)

**Steps**
1. Open `main_controller/main.ino` in Arduino IDE.
2. In the tunables section, set your **board pins** and **motor limits**.
3. Select board + port → **Upload**.

---

## 🔌 Pin Map Template (edit in `main.ino`)
```cpp
// Hub motors (left/right)
#define H1_PWM 5
#define H1_IN1 7
#define H1_IN2 8
#define H2_PWM 6
#define H2_IN1 9
#define H2_IN2 10

// Central bevel motors (left/right)
#define C1_PWM 3
#define C1_IN1 11
#define C1_IN2 12
#define C2_PWM 4
#define C2_IN1 A2
#define C2_IN2 A3

// Rack actuator (shared or per-side)
#define R_PWM  2
#define R_IN1  A0
#define R_IN2  A1
