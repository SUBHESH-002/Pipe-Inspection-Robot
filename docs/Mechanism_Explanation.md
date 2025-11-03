# Mechanism Explanation — Active Omni PipeBot (2-Wheel Module + Rack Extension)

This document explains the wheel unit inspired by the Ducati Upriser active omni (two motor inputs per wheel) and the rack-and-pinion that pushes both wheels outward to grip the pipe wall.

## 1) What the wheel really is
Each wheel is a **2-DOF differential**:
- **Hub motor (ωₕ)** spins the main hub → creates forward/backward motion.
- **Central bevel gear motor (ω𝚌)** drives the eight 45° rollers via a bevel-gear train → creates sideways motion.
- When ω𝚌 = ωₕ, rollers don’t spin relative to the hub → behaves like a normal wheel.
- When the hub is held and ω𝚌 spins, rollers generate pure lateral thrust.

> In practice we use **two such wheels** placed left/right, separated by track **B**, and a **rack-extension** that sets the wall contact preload.

## 2) Why this works in a pipe
- The pipe gives us a consistent, smooth contact surface with known inner diameter (ID).
- The **rack** sets a normal force **N** at each wheel. With friction **μ**, two wheels can hold against gravity in vertical segments:
  
  \[
  2 \mu N \ge m g \quad\Rightarrow\quad N \ge \frac{m g}{2 \mu}
  \]

- By commanding wheel inputs, we can move **axially** (along pipe), **circumferentially** (around pipe), or **helically** (combo).

## 3) Kinematic summary (per wheel → robot)
Let:
- \(R_h\) = main rolling radius,
- \(r_r\) = roller radius,
- \(\alpha \approx 45^\circ\) = roller axle angle,
- \(G\) = central-to-roller gear ratio,
- \(\kappa = G\,r_r \cos\alpha\).

**Single wheel surface velocities**
- Axial component: \(v_x = R_h \,\omega_h\)
- Lateral component: \(v_y = \kappa\,(\omega_c - \omega_h)\)

**Two-wheel body twist (track \(B\))**
\[
\begin{aligned}
v_x &= \frac{R_h}{2}(\omega_{h1} + \omega_{h2})\\
v_y &= \frac{\kappa}{2}\big[(\omega_{c1}-\omega_{h1}) + (\omega_{c2}-\omega_{h2})\big]\\
\omega_z &= \frac{R_h}{B}(\omega_{h2} - \omega_{h1})
\end{aligned}
\]

This separation is useful: **hubs** control forward + yaw, while the **central bevels** add pure sideways without adding yaw (if applied symmetrically).

## 4) Rack-and-pinion preload
- Target normal force per wheel \(N \ge \frac{m g}{2\mu}\) with 30–50% margin.
- If pinion pitch radius is \(\rho_p\), required torque to set \(N\) (near-radial link):
  \[
  T_{\text{pinion}} \approx N\,\rho_p
  \]
  Non-radial arm at angle \(\beta\) needs \(F_{\text{rack}} \approx N/\cos\beta\).

**Drive torque per wheel for steady vertical climb**:
\[
\tau_{\text{wheel}} \approx \frac{m g R_h}{2}
\]
(Add 1.5–2× headroom for losses, joints, and transitions.)

## 5) Control recipes (quick)
- **Straight:** set \(\omega_{h1}=\omega_{h2}=v_x/R_h\), \(\omega_{c1}=\omega_{h1}\), \(\omega_{c2}=\omega_{h2}\).
- **Sideways:** set \(\omega_{h1}=\omega_{h2}=0\), and \(\omega_{c1}=\omega_{c2}=v_y/\kappa\).
- **Yaw in place:** set \(\omega_{h2}=-\omega_{h1}=(B\,\omega_z)/(2R_h)\); set \(\omega_{c1}=\omega_{h1}\), \(\omega_{c2}=\omega_{h2}\).
- **Helix:** combine the above; keep sideways symmetric so yaw doesn’t drift.

## 6) Images
Place reference images in `docs/images/` and link here:
- `docs/images/wheel_cutaway.png` – bevel differential & rollers
- `docs/images/rack_extension.png` – rack, pinion, and wheel carriages

> After you upload, embed them like:
>
> `![Active omni cutaway](images/wheel_cutaway.png)`
>
> `![Rack extension concept](images/rack_extension.png)`

## 7) What to verify next (Stage 3 checklist)
- Fusion Motion Study: **rack stroke vs. pipe ID**, contact clearances in bends.
- Compute \(N, \tau_{\text{wheel}}, T_{\text{pinion}}\) using your \(m, \mu, R_h, \rho_p\).
- Pick motors/ratios to deliver ≥1.5× torque targets.
