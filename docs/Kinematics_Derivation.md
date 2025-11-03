# 📐 Kinematics Derivation — Active Omni PipeBot (Two-Wheel Configuration)

This document formalizes the mathematical model of the **active omni differential wheel** and its integration into a **two-wheel pipe-inspection robot**.  
It provides both **forward** (motor → motion) and **inverse** (motion → motor) kinematics for implementation in simulation or firmware.

---

## 1️⃣ System Overview

Each wheel unit has **two motor inputs**:
- **Hub motor (ωₕ)** → rotates the wheel hub, generating forward motion.  
- **Central bevel motor (ω𝚌)** → spins the roller differential, generating lateral motion.

Each roller is mounted at a constant angle α (≈ 45°) to the hub’s tangential direction.  
The effective roller gearing ratio is **G**, and roller radius **rᵣ**.

---

## 2️⃣ Fundamental Relations

### 2.1 Roller Speed
Because the rollers are gear-driven by the central bevel,
\[
\omega_r = G\,(\omega_c - \omega_h)
\]
This expresses the differential nature — if both motors spin equally, the rollers do not rotate relative to the hub.

### 2.2 Wheel Contact-Point Velocity
At the ground contact:
\[
v_x = R_h\,\omega_h
\]
\[
v_y = r_r\,\omega_r\,\cos\alpha = G\,r_r\,\cos\alpha\,(\omega_c - \omega_h)
\]
Define the constant
\[
\kappa = G\,r_r\,\cos\alpha
\]
then
\[
v_y = \kappa(\omega_c - \omega_h)
\]

---

## 3️⃣ Forward Kinematics (Single Wheel → Robot Velocity)

For the left and right wheel modules:

\[
\begin{aligned}
v_{x1} &= R_h\,\omega_{h1} \\
v_{x2} &= R_h\,\omega_{h2} \\
v_{y1} &= \kappa(\omega_{c1} - \omega_{h1}) \\
v_{y2} &= \kappa(\omega_{c2} - \omega_{h2})
\end{aligned}
\]

Assuming both wheels are coplanar and separated by track distance **B**,  
the robot’s body-frame velocities become:

\[
\boxed{
\begin{aligned}
v_x &= \frac{R_h}{2}(\omega_{h1} + \omega_{h2}) \\
v_y &= \frac{\kappa}{2}\big[(\omega_{c1} - \omega_{h1}) + (\omega_{c2} - \omega_{h2})\big] \\
\omega_z &= \frac{R_h}{B}(\omega_{h2} - \omega_{h1})
\end{aligned}
}
\]

---

## 4️⃣ Inverse Kinematics (Desired → Motor Speeds)

Given desired body-frame velocities \(v_x, v_y, \omega_z\),  
determine required motor angular speeds.

### 4.1 Hub Motors
\[
\begin{aligned}
\omega_{h1} &= \frac{v_x}{R_h} - \frac{B\,\omega_z}{2R_h} \\
\omega_{h2} &= \frac{v_x}{R_h} + \frac{B\,\omega_z}{2R_h}
\end{aligned}
\]

### 4.2 Central Bevel Motors
Assuming symmetric lateral command:
\[
(\omega_{c1} - \omega_{h1}) = (\omega_{c2} - \omega_{h2}) = \frac{v_y}{\kappa}
\]
then
\[
\begin{aligned}
\omega_{c1} &= \omega_{h1} + \frac{v_y}{\kappa} \\
\omega_{c2} &= \omega_{h2} + \frac{v_y}{\kappa}
\end{aligned}
\]

---

## 5️⃣ Matrix Form (for Code Implementation)

\[
\begin{bmatrix}
v_x \\[4pt] v_y \\[4pt] \omega_z
\end{bmatrix}
=
\underbrace{
\begin{bmatrix}
\dfrac{R_h}{2} & \dfrac{R_h}{2} & 0 & 0 \\
-\dfrac{\kappa}{2} & -\dfrac{\kappa}{2} & \dfrac{\kappa}{2} & \dfrac{\kappa}{2} \\
-\dfrac{R_h}{B} & \dfrac{R_h}{B} & 0 & 0
\end{bmatrix}
}_{\text{Jacobian }J}
\begin{bmatrix}
\omega_{h1}\\[4pt]\omega_{h2}\\[4pt]\omega_{c1}\\[4pt]\omega_{c2}
\end{bmatrix}
\]

Inverse kinematics then use \(J^{-1}\) or the closed-form equations above.

---

## 6️⃣ Special-Case Motions

| Mode | Motor Conditions | Result |
|------|------------------|---------|
| **Forward/Backward** | ωₕ₁ = ωₕ₂ ≠ 0; ω𝚌₁ = ω𝚌₂ = ωₕ | Pure axial motion |
| **Sideways (circumferential)** | ωₕ₁ = ωₕ₂ = 0; ω𝚌₁ = ω𝚌₂ ≠ 0 | Pure lateral motion |
| **Yaw rotation** | ωₕ₂ = −ωₕ₁; ω𝚌₁ = ωₕ₁; ω𝚌₂ = ωₕ₂ | Spin in place |
| **Helical climb** | ωₕ’s and ω𝚌’s non-zero | Combined motion along a spiral path |

---

## 7️⃣ Implementation Notes

- **Sampling rate:** ≥ 100 Hz for smooth velocity blending.  
- **Feed-forward control:** Use kinematic mapping to generate target RPMs.  
- **Feedback:** IMU yaw and wheel encoders close the loop on \(v_x, v_y, \omega_z\).  
- **Calibration:** Empirically adjust \(R_h\) and \(\kappa\) via measured vs. predicted motion.

---

## 8️⃣ Typical Parameter Values
| Parameter | Symbol | Nominal | Unit |
|------------|:--:|:--:|:--:|
| Wheel radius | \(R_h\) | 0.025 | m |
| Roller radius | \(r_r\) | 0.008 | m |
| Roller angle | \(\alpha\) | 45 ° | — |
| Gear ratio | \(G\) | 1.5 : 1 | — |
| Track width | \(B\) | 0.10 | m |

Then \(\kappa = G\,r_r\,\cos\alpha ≈ 0.0085 \text{m}\).

---

## 9️⃣ Validation Targets (Stage 3)
- Run **Fusion 360 Motion Study** → extract angular speeds & linear displacement.  
- Compare simulated \(v_x,v_y,\omega_z\) with analytical predictions.  
- Verify coupling independence: lateral commands should not induce yaw.  
- Export test data to `/analysis/kinematics_validation.csv`.

---

*Prepared for integration with firmware module `inverse_kinematics.cpp` and simulation notebook `analysis/kinematics.ipynb`.*
