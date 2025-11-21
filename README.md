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

Let $r(t)$ be the reference of angular position, $y(t)$ the angular position, $u(t)$ the control signal, and $e(t)$ the tracking error. For a PID controller the following response is obtained:
<p align="center">
<img width="733" height="395" alt="dc_motor_data_pid" src="https://github.com/user-attachments/assets/aa734a0e-5273-4374-818e-98b97d847cf7" />
</p>

For a PR controller the following response is obtained:
<p align="center">
<img width="733" 395="1772" alt="dc_motor_data_pr" src="https://github.com/user-attachments/assets/e0c402ff-79f7-49b7-af84-ad3468cd8b36" />
</p>

For a repetitive controller the following response is obtained:
<p align="center">
<img width="733" 395="1772" alt="dc_motor_data_repetitive" src="https://github.com/user-attachments/assets/1e52b4d8-c95d-4932-bb62-966efbc2aeac" />
</p>
