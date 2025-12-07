# DC motor position control

A control system project for regulating the angular position of a direct current (DC) motor using different controllers.

Initially, the practical aspects of constructing the physical experiment are presented. In sequence, digital **proportional-integral-derivative (PID)**, **proportional-resonant (PR)**, **proportional-multi-resonant (PMR)** and **proportional-repetitive controllers** are implemented. The data is acquired via a serial communication protocol and .csv results can be plotted witth Python or Matlab scripts.

The following programs are available:
- [Relay method](./dc_motor_relay_method)
- [PID controller](./dc_motor_position_control_pid)
- [PR controller](./dc_motor_position_control_pr)
- [PMR controller](./dc_motor_position_control_pmr_optimized)
- [Repetitive controller](./dc_motor_position_control_repetitive)

## Physical experiment

The physical experiment is presented bellow:
<p align="center">
<img width="500" height="395" alt="dc_motor_data_pid" src="https://github.com/user-attachments/assets/252c9af2-f54f-4d89-bdc0-c545092065df" />
</p>

## Experimental results

Let $r(t)$ be the reference of angular position, $y(t)$ the angular position, $u(t)$ the control signal, and $e(t)$ the tracking error. First, a relay experiment should be performed to obtain the critical gain $K_{u}$ and critical period $P_u$ needed to tune (some of) the controllers:
<p align="center">
<img width="733" height="395" alt="dc_motor_data_relay" src="https://github.com/user-attachments/assets/48136c1f-40c5-497f-83a5-fd6ec46e92f8" />
</p>

Assuming a problem of sinusoidal reference tracking with a 90 degrees amplitude and frequency of 0.1 Hz, for a tuned PID controller the following response is obtained:
<p align="center">
<img width="733" height="395" alt="dc_motor_data_pid" src="https://github.com/user-attachments/assets/b2a49fdc-78cc-4410-9150-76d2e875ca93" />
</p>

Cosidering a PR controller the following response is obtained:
<p align="center">
<img width="733" 395="1772" alt="dc_motor_data_pr" src="https://github.com/user-attachments/assets/ee695dd0-672f-43c9-b457-f27c9b1216aa" />
</p>

Cosidering a repetitive controller the following response is obtained:
<p align="center">
<img width="733" 395="1772" alt="dc_motor_data_repetitive" src="https://github.com/user-attachments/assets/a10ece36-b811-4a76-928f-3bf25d5db06c" />
</p>

Assuming a problem of triangular reference tracking with a 90 degrees amplitude and frequency of 0.1 Hz, for a PR controller the following response is obtained:
<p align="center">
<img width="733" 395="1772" alt="dc_motor_data_pmr_triangular_h1" src="https://github.com/user-attachments/assets/edde3e97-e720-48d3-98be-2335a7a10dc5" />
</p>

Cosidering a PMR controller with $h = 6$ resonant modes the following response is obtained:
<p align="center">
<img width="733" 395="1772" alt="dc_motor_data_pmr_triangular_h6" src="https://github.com/user-attachments/assets/794d75c1-2af4-4dfb-80a3-4f9272ded1fa" />
</p>
