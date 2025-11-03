# Active Omni-Wheel Pipe Inspection Robot — CAD Model

## Overview
This CAD model represents a **Ducati Upriser–style active omni-wheel system** designed for a compact **pipe inspection robot**. The design enables the robot to navigate, climb, and inspect pipelines ranging from **150 mm to 200 mm** in diameter, maintaining full control in both horizontal and vertical orientations.

---

## Design Concept
The robot uses **two active omni-wheels** mounted on a **rack expansion mechanism**.  
Each wheel features **dual-drive inputs**:
- **Hub Motor (ωₕ):** Controls the main rolling motion for forward/backward travel.  
- **Bevel-Differential Motor (ω𝚌):** Drives the rollers for sideways movement, enabling omnidirectional control.  

By controlling both drives, the robot can perform:
- Forward and backward motion (**vₓ**)  
- Lateral (sideways) motion (**v_y**)  
- Yaw rotation (**ω_z**)  
- Combined **helical motion** for vertical climbing  

---

## Mechanical Highlights
- **Rack-based preload system** pushes wheels outward to maintain wall contact.  
- **Lightweight, symmetric frame** ensures balanced center of mass.  
- **Dual-input omni-wheels** enable precise control in tight pipe spaces.  
- **Compact assembly** (≤140 mm diameter) fits through bends and T-junctions smoothly.  

---

## Performance Goals
- **Pipe diameter range:** 150–200 mm  
- **Robot weight:** ≤ 4 kg  
- **Climb capability:** 0–90° inclines  
- **Traction control:** Adjustable via rack preload torque  
- **Sensors (planned):** Camera, IMU, and gas sensor for internal inspection  

---

## Files
- `model001.f3d` — Main Fusion 360 CAD assembly  
- `/mech/drawings/` — Technical drawings and sub-assemblies  
- `/mech/calcs/` — Torque and grip force analysis  

---

## Next Steps
- Run **torque and motion validation** in Fusion 360.  
- Integrate **electronics layout** and **sensor mounts**.  
- Generate **exploded view** and **BOM** for fabrication.  

---

*Author: Subhesh Kumar*  
*Project: Pipe Inspection Robot (Active Omni Module)*  
