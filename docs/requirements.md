# System Requirements – Pipe Inspection Robot

## 1. Mechanical Requirements
- Must fit within **150 – 200 mm pipe ID** range.  
- Overall robot diameter ≤ 140 mm for Ø200 mm pipe with ≥ 5 mm wall clearance.  
- Maintain traction and stability on **0° – 90° inclines**.  
- Capable of turning through **≥ 150 mm bend radius** without jamming.  
- **Total mass ≤ 4 kg**, including all subsystems.  
- Support **bidirectional motion** and **modular assembly** for maintenance and part replacement.

---

## 2. Electrical Requirements
- Power from compact **Li-ion battery pack** (≥ 30 min operation).  
- Integrated **motor drivers** for differential or multi-wheel control.  
- Sensors: **Camera**, **IMU**, **Gas sensor**, and **Wheel encoders**.  
- **Microcontroller / SBC** (ESP32 / Raspberry Pi) for onboard processing.  
- Safety features for **over-current, low-voltage, and thermal cutoff**.

---

## 3. Control and Software Requirements
- Encoder-based **odometry** with drift ≤ 5% over 5 m straight run.  
- Optional **autonomous navigation** with obstacle avoidance.  
- **Telemetry:** transmit video + sensor data to operator station.  
- **Real-time monitoring interface** (wired or wireless).  
- Compatibility with **open-source frameworks** (ROS optional).

---

## 4. Performance Requirements
- **Min speed:** 0.1 m/s **Max speed:** 0.3 m/s (flat)  
- Operate for **≥ 30 min** per charge cycle.  
- Maintain **grip on steel/PVC surfaces** with μ ≥ 0.5.  
- Stable CoG during vertical climb and bend traversal.

---

## 5. Environmental & Safety Requirements
- Operate in confined pipes with **humidity ≤ 90%**, temp 0–50 °C.  
- Tolerate **mild shocks and vibration** during motion.  
- Basic **IP54 sealing** against dust and splashes.  
- Comply with **non-hazardous, low-voltage (< 24 V DC)** operation.

---

## 6. Testing & Validation
- Clearance and fit tests in Ø150 mm / Ø200 mm pipes.  
- Incline (45°–90°) traction test.  
- Bend & T-junction traversal demonstration.  
- Odometry accuracy and telemetry latency measurements.

---

**Document Version:** 1.1  
**Last Updated:** November 2025
