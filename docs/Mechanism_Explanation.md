# ⚙️ Mechanism Explanation — Active Omni PipeBot (2-Wheel Module with Rack Extension)

This document describes the wheel module inspired by the **Ducati Upriser active omni system**.  
Each wheel provides **two independent degrees of freedom (2-DOF)** through differential gearing, while a **rack-and-pinion** mechanism deploys both wheels outward to ensure stable wall contact inside a pipe.

---

## 1️⃣ Wheel Concept

Each wheel acts as a **two-motor differential drive**:
- **Hub motor (ωₕ):** rotates the main wheel hub → produces forward or backward motion.
- **Central bevel-gear motor (ω𝚌):** drives eight 45° rollers mounted on bevel gears → produces lateral motion.

**Modes of operation**
- When **ω𝚌 = ωₕ**, there is no relative motion between hub and central gear → the wheel behaves as a **conventional wheel**.
- When the hub is held still and **ω𝚌 ≠ 0**, the bevel train spins the rollers, creating **pure sideways (lateral) thrust**.

> The robot uses **two such wheels**, placed symmetrically left and right (track distance **B**) and mounted on a rack that controls wall-contact preload.

---

## 2️⃣ Operating Principle in a Pipe

- The pipe’s inner wall provides a **consistent cylindrical surface** for traction.
- A **rack-and-pinion** mechanism pushes both wheel carriages outward to maintain contact with the pipe wall.
- Each wheel applies a normal force **N**, and with friction coefficient **μ**, two wheels can support the robot’s weight even in vertical orientation:

\[
2\mu N \geq mg \quad\Rightarrow\quad N \geq \frac{mg}{2\mu}
\]

- By commanding combinations of wheel inputs, the robot can move:
  - **Axially** (along the pipe)
  - **Circumferentially** (around the pipe)
  - **Helically** (combined motion)

---

## 3️⃣ Kinematic Summary

Define parameters:
| Symbol | Meaning |
|:--|:--|
| \(R_h\) | Main wheel (hub) radius |
| \(r_r\) | Roller radius |
| \(\alpha\) | Roller axle angle (≈ 45°) |
| \(G\) | Gear ratio between central and roller bevel gears |
| \(\kappa = G\,r_r\cos\alpha\) | Effective lateral scaling constant |

### Single-Wheel Surface Velocities
\[
\begin{aligned}
v_x &= R_h\,\omega_h \\
v_y &= \kappa\,(\omega_c - \omega_h)
\end{aligned}
\]

### Two-Wheel Body Twist (Track Distance \(B\))
\[
\begin{aligned}
v_x &= \frac{R_h}{2}(\omega_{h1} + \omega_{h2}) \\
v_y &= \frac{\kappa}{2}\big[(\omega_{c1}-\omega_{h1}) + (\omega_{c2}-\omega_{h2})\big] \\
\omega_z &= \frac{R_h}{B}(\omega_{h2} - \omega_{h1})
\end{aligned}
\]

- The **hub motors** control **forward motion and yaw**,  
- The **central bevel motors** produce **pure lateral motion** (if symmetric).

---

## 4️⃣ Rack-and-Pinion Preload

To ensure sufficient frictional grip:

\[
N \ge \frac{mg}{2\mu}
\]

Add 30–50 % safety margin to account for pipe ovality and surface variation.

If the pinion driving the rack has pitch radius **ρₚ**,  
the torque required per pinion is:

\[
T_{\text{pinion}} = N\,\rho_p
\]

For non-radial arms at an angle **β**, the rack force increases:

\[
F_{\text{rack}} = \frac{N}{\cos\beta}
\]

**Drive torque for steady vertical climb:**

\[
\tau_{\text{wheel}} = \frac{mgR_h}{2}
\]

Use at least **1.5 × to 2 × headroom** for frictional losses and transient load changes.

---

## 5️⃣ Basic Motion Commands

| Motion Type | Hub Motor Command | Central Motor Command |
|--------------|------------------|------------------------|
| **Straight** | \(\omega_{h1}=\omega_{h2}=v_x/R_h\) | \(\omega_{c1}=\omega_{h1},\; \omega_{c2}=\omega_{h2}\) |
| **Sideways** | \(\omega_{h1}=\omega_{h2}=0\) | \(\omega_{c1}=\omega_{c2}=v_y/\kappa\) |
| **Yaw in Place** | \(\omega_{h2}=-\omega_{h1}=\frac{B\,\omega_z}{2R_h}\) | \(\omega_{c1}=\omega_{h1},\; \omega_{c2}=\omega_{h2}\) |
| **Helical Motion** | Combine forward + sideways; keep lateral commands symmetric to prevent yaw drift. |

---

## 6️⃣ Reference Images

After uploading visuals, embed them as follows:

```markdown
![Active omni cutaway](images/wheel_cutaway.png)
![Rack extension concept](images/rack_extension.png)
