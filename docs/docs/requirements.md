# System Requirements – Pipe Inspection Robot

## 1. Mechanical Requirements
- Must fit within **150–200 mm pipe ID** range.
- Should maintain traction on **0°–90° inclines**.
- Capable of turning through **minimum pipe bend radius** without jamming.
- **Total mass ≤ 4 kg**, including sensors, batteries, and electronics.
- Must support **bidirectional movement** and **modular assembly** for maintenance.

---

## 2. Electrical Requirements
- Power supply from compact Li-ion battery pack.
- Integrated **motor drivers** for differential or multi-wheel control.
- **Sensors:** Camera, IMU, gas sensor, and wheel encoders.
- Microcontroller or SBC (e.g., Raspberry Pi / ESP32) for data processing.
- Safety features for overcurrent, low voltage, and thermal protection.

---

## 3. Control and Software Requirements
- Encoder-based **odometry** for movement estimation.
- Optional **autonomous navigation** with obstacle detection.
- **Telemetry**: Send data (camera + sensor readings) to ground station.
- Real-time **monitoring and control interface**.
- Compatibility with open-source frameworks (ROS optional).

---

## 4. Performance Requirements
- Minimum travel speed: **0.1 m/s** (horizontal)  
- Maximum speed: **0.3 m/s** (flat terrain)
- Operational duration: **≥ 30 minutes** per battery cycle.
- Maintain stability and grip on steel or PVC surfaces.

---

## 5. Environmental and Safety Requirements
- Operate in **confined spaces** with humidity ≤ 90%.
- Tolerate **mild vibrations and shocks** during movement.
- Comply with **non-hazardous operation** guidelines.

---

**Document Version:** 1.0  
**Last Updated:** October 2025
