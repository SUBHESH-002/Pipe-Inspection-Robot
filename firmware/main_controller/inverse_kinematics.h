#pragma once
#include <Arduino.h>

/*
 * Inverse kinematics for two active-omni wheels
 *
 * Inputs:
 *   vx  [m/s], vy [m/s], wz [rad/s]
 *   Rh  hub radius [m]
 *   kappa = G * rr * cos(alpha) [m]
 *   B   track width [m]
 *
 * Outputs (by reference):
 *   oh1, oh2  hub angular speeds [rad/s]
 *   oc1, oc2  central bevel speeds [rad/s]
 *
 * Equations (docs/Kinematics_Derivation.md):
 *   oh1 = (vx/Rh) - (B*wz)/(2*Rh)
 *   oh2 = (vx/Rh) + (B*wz)/(2*Rh)
 *   oc1 = oh1 + (vy/kappa)
 *   oc2 = oh2 + (vy/kappa)
 */

static inline void invKin_twoWheel(float vx, float vy, float wz,
                                   float Rh, float kappa, float B,
                                   float &oh1, float &oh2, float &oc1, float &oc2)
{
  // Guard for zero/near-zero params
  if (Rh <= 1e-6f) Rh = 1e-6f;
  if (kappa == 0.0f) kappa = 1e-6f;

  const float vx_over_R = vx / Rh;
  const float half_Bwz_over_R = (B * wz) / (2.0f * Rh);
  oh1 = vx_over_R - half_Bwz_over_R;
  oh2 = vx_over_R + half_Bwz_over_R;

  const float vy_over_k = vy / kappa;
  oc1 = oh1 + vy_over_k;
  oc2 = oh2 + vy_over_k;
}
