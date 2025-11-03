# 🧱 3D Print Settings — Active Omni PipeBot

These are baseline print profiles for structural parts, the wheel hub, and TPU rollers. Adjust per your printer/material.

---

## 1) Structural Parts (chassis, carriages, rack mounts)
- **Material:** PETG (preferred) or ABS  
- **Nozzle:** 0.4 mm (0.6 mm for faster/stronger)  
- **Layer height:** 0.20 mm (0.28 mm acceptable)  
- **Walls:** 4 perimeters  
- **Top/Bottom:** 5–6 layers  
- **Infill:** 35–45 % Gyroid/Cubic  
- **Temp:** PETG 235–245 °C / Bed 80–85 °C  
- **Cooling:** 20–40 % after layer 2  
- **Orientation:**  
  - Rack mounts: orient so tooth load is **in-plane** with layers  
  - Carriages: orient linear-bearing/slider bores vertical; use support blockers if needed  
- **Supports:** Tree/normal where overhangs > 55°  
- **Post-process:** Deburr rack/pinion teeth, light PTFE grease on guides

## 2) Wheel Hubs & Differential Housing
- **Material:** PETG or ABS; consider CF-PETG for stiffness  
- **Walls:** 5 perimeters  
- **Infill:** 40–60 %  
- **Critical:** keep bore diameters within ±0.1 mm; ream motor coupler bores; heat-set inserts for M3

## 3) Omni Rollers (TPU)
- **Material:** TPU 95A (or 85A for more grip)  
- **Nozzle:** 0.4 mm  
- **Layer height:** 0.20–0.24 mm  
- **Walls:** 2–3 perimeters  
- **Infill:** 15–20 %  
- **Speed:** 20–30 mm/s (slow for consistency)  
- **Retraction:** Minimal (0.5–1.0 mm)  
- **Tip:** Sand lightly with fine grit to improve traction; avoid solvents

## 4) Rack & Pinion (if printed)
- **Material:** PLA+ (dimensionally stable) or PETG  
- **Tooth profile:** Involute module matching your CAD (e.g., Mod 1)  
- **Infill:** 60 %  
- **Walls:** 5 perimeters  
- **Fit:** Ensure pitch radius ρₚ matches torque sizing from `/analysis/torque_analysis.ipynb`

## 5) Tolerances & Inserts
- Motor mount holes: design at nominal Ø, drill/ream to final  
- Use **M3 heat-set inserts** (brass) for repeatable assembly  
- Shafts: prefer D-shaped or spline couplers to avoid set-screw slip

## 6) QA Checklist
- [ ] Rack slides smoothly along full travel (no binding)  
- [ ] Pinion meshes across travel (no tight spots)  
- [ ] Wheel hubs run true (≤0.3 mm radial runout)  
- [ ] Omni rollers spin freely on axles, no rubbing  
- [ ] Dry fit electronics bay; cables clear moving parts

## 7) STL/STEP Index (update as you add files)
- `cad/WheelModule.stl` — hub + roller seats  
- `cad/RackCarriageLeft.stl`, `cad/RackCarriageRight.stl`  
- `cad/PinionGear.step`, `cad/Rack.step`  
- `cad/ChassisMain.stl`  
