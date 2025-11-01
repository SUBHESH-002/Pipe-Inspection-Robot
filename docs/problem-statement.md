# Problem Statement – Pipe Inspection Robot

## Objective
Design and develop a compact, mobile robot capable of inspecting the internal sections of industrial pipelines with minimal human intervention. The robot must navigate horizontal, inclined, and vertical segments—including 150 mm radius bends and T-junctions—while transmitting real-time visual and sensory data for inspection and analysis.

---

## Pipe Specifications
- **Internal Diameter Range:** 150 mm – 200 mm  
- **Maximum Outer Envelope (Robot):** ≤ 140 mm (for 200 mm pipe) with ≥ 5 mm wall clearance  
- **Minimum Bend Radius:** ≥ 150 mm (standard industrial bend)  
- **Incline Angles:** 0° to 90° (horizontal → vertical orientation)

---

## Performance Targets
- **Travel Speed:** 0.1 – 0.3 m/s (adjustable by slope and terrain)  
- **Bidirectional Movement:** Forward and reverse with positional drift ≤ 5% over 5 m  
- **Total Mass:** ≤ 4 kg (including batteries, sensors, and chassis)  
- **Operational Duration:** ≥ 30 minutes per battery cycle  

---

## Sensor & Instrumentation Requirements
- **Camera Module:** High-resolution live video for internal visual inspection  
- **IMU (Inertial Measurement Unit):** Orientation, tilt, and acceleration feedback  
- **Gas Sensor:** Detection of hazardous gases (e.g., CH₄, CO₂, H₂S)  
- **Wheel Encoders:** Odometry and differential movement feedback  

---

## Functional Goals
1. Semi-autonomous or autonomous navigation through pipes and bends.  
2. Reliable real-time acquisition and transmission of video and sensor data.  
3. Stable traversal through horizontal, vertical, and T-junction segments.  
4. Modular, lightweight, and serviceable mechanical design.  
5. Safe and energy-efficient electrical system with thermal and overload protection.

---

## Validation & Testing
Prototype will be validated through:
- Horizontal and vertical mobility tests inside Ø150 mm – Ø200 mm pipes.  
- Bend and T-junction traversal trials.  
- Encoder-based odometry accuracy checks.  
- Real-time telemetry test for camera and gas sensor data.

---

**Document Version:** 1.1  
**Last Updated:** November 2025
