# DC motor position control

A control system project for regulating the angular position of a direct current (DC) motor using different controllers.

Initially, the practical aspects of constructing the physical experiment are presented. In sequence digital proportional-integral-derivative (PID), proportional-resonant (PR), and repetitive controllers are implemented. The data is acquired via a serial communication protocol and results can be plotted with a desired application.

The following programs are available:
- [Relay method](./dc_motor_relay_method)
- [PID controller](./dc_motor_position_control_pid)
- [PR controller](./dc_motor_position_control_pr)
- [Repetitive controller](./dc_motor_position_control_repetitive)

## Physical experiment

The physical experiment is presented bellow
<p align="center">
<img width="500" height="395" alt="dc_motor_data_pid" src="https://github.com/user-attachments/assets/d628d326-d182-4be2-b000-68d90202edd6" />
<img width="500" height="395" alt="dc_motor_data_pid" src="https://github.com/user-attachments/assets/e1b99fd0-33b4-4536-8ad6-5086f1dbdcb5" />
</p>

## Experimental results

Let $r(t)$ be the reference of angular position, $y(t)$ the angular position, $u(t)$ the control signal, and $e(t)$ the tracking error. First, a relay experiment should be performed in order to obtain the critical $K_{u}$ gain and critical period $P_u$:
<p align="center">
<img width="733" height="395" alt="dc_motor_data_relay" src="https://github.com/user-attachments/assets/48136c1f-40c5-497f-83a5-fd6ec46e92f8" />
</p>

Assuming a problem of sinusoidal reference tracking with an 90 degrees amplitude, for a PID controller the following response is obtained:
<p align="center">
<img width="733" height="395" alt="dc_motor_data_pid" src="https://github.com/user-attachments/assets/b2a49fdc-78cc-4410-9150-76d2e875ca93" />
</p>

For a PR controller the following response is obtained:
<p align="center">
<img width="733" 395="1772" alt="dc_motor_data_pr" src="https://github.com/user-attachments/assets/1f75fb73-9006-47a6-b80f-15246d4d2d92" />
</p>

For a repetitive controller the following response is obtained:
<p align="center">
<img width="733" 395="1772" alt="dc_motor_data_repetitive" src="https://github.com/user-attachments/assets/7d06a61d-ee27-4981-be56-7f738cf4a47e" />
</p>
