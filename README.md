# RoboArm
Custom designed 6 DOF Robotic Arm using ESP32 and real time servo motor control.

This project focuses on the design, fabrication, and development of a six-degree-of-freedom (6-DOF) robotic arm capable of performing pick-and-place operations. The arm was designed entirely from scratch, including the mechanical structure, electronics integration, control system, and custom PCB.
The robotic arm is currently controlled through a smartphone application via Bluetooth communication with an ESP32 microcontroller. Joint-level control has been successfully implemented, allowing real-time operation.

**Main Components**

1) ESP32 Microcontroller
2) PCA9685 Servo Motor Driver
3) MG90 & MG996 Servo Motors
4) Custom PCB
5) NiMH Batteries

Initially, the robotic arm was assembled using direct wiring between components. Later, a custom PCB was designed and manufactured to improve reliability and simplify assembly.

The ESP32 connects over bluetooth using Dabble, a mobile application, allowing control over the microcontroller wirelessly. Its Gamepad buttons have been mapped to specific motor movements which allow joint-based arm control.

Future upgrades of the robotic arm will include an ESP32-CAM module mounted near the gripper, and Inverse Kinematics for ease of arm control.
