# 🧾 Stage Progress Report — Pipe Inspection Robot

This document tracks the development progress of the **Active Omni PipeBot** project against the design stages defined in the *Mechanical Design* specification.

---

## 📅 Summary Timeline

| Stage | Description | Deliverables | Status | % Complete | Last Updated |
|:--:|:--|:--|:--:|:--:|:--:|
| **1** | **Conceptual Design & Kinematic Configuration** | Multiple CAD sketches, mechanism concepts, motion constraints, clearance study | ✅ Completed | **100 %** | Oct 2025 |
| **2** | **Torque & Drive Mechanism Analysis** | Torque model, force equations, motor sizing, gear ratio optimization | 🟨 In progress – analytical model derived; numerical validation pending | **70 %** | Nov 2025 |
| **3** | **Component Placement & Mechanical Integration** | Internal frame design, camera/IMU/gas-sensor mounts, wiring channels | ⏳ Queued – awaiting motor dimensions and torque results | **40 %** | — |
| **Bonus** | **Final Assembly & Mechanical Validation** | Full Fusion assembly, motion + stress analysis, BOM, CoG shift validation | 🔜 Planned | **10 %** | — |
| **5** | **Firmware & Control Integration** | Inverse-kinematics firmware, encoder + IMU feedback, control loop testing | 🔜 Pending (after hardware prototype) | **0 %** | — |

---

## 📊 Detailed Notes per Stage

### 🧩 Stage 1 – Conceptual Design (✔ Completed)
- Chosen configuration: **two-wheel active-omni with rack-extension**.  
- Derived kinematics and wheel equations.  
- Verified geometry in Fusion 360 (STL export ready).  
- Balanced weight distribution and ensured 5 mm radial clearance inside 150–200 mm pipes.

### ⚙️ Stage 2 – Torque & Drive Analysis (🟨 In Progress)
- Analytical torque equations:
  - \( \tau_{\text{wheel}} = \frac{mgR_h}{2} \)
  - \( T_{\text{pinion}} = N\rho_p \), with \( N = \frac{mg}{2\mu} \)
- Simulation pending in **Fusion 360 Motion Study** for:
  - Vertical climb (0°, 45°, 90°)
  - Rack preload vs. pipe ID
- To add: `/analysis/torque_analysis.ipynb` for numeric evaluation.

### 🧱 Stage 3 – Mechanical Integration (⏳ Next)
- Design sensor frames (camera FOV 120°–150° tilt).  
- Place IMU near CG, isolate battery compartment.  
- Validate wiring channels via **section analysis**.  
- Output: `Component_Layout.f3d` + `Mechanical_Integration_Report.pdf`.

### 🧮 Bonus – Assembly & Validation (🔜)
- Perform collision & clearance check through bends and T-junctions.  
- Evaluate CG shift vs. tilt angle (±45°).  
- Run stress simulation on rack arms (load = N).  
- Deliver: `Final_Assembly_BOM.xlsx`, exploded view renders.

### 💻 Stage 5 – Firmware & Control (🔜)
- Implement inverse kinematics in C++ / Arduino:
  ```cpp
  omega_h1 = (vx/Rh) - (B*omega_z)/(2*Rh);
  omega_h2 = (vx/Rh) + (B*omega_z)/(2*Rh);
  omega_c1 = omega_h1 + (vy/kappa);
  omega_c2 = omega_h2 + (vy/kappa);
