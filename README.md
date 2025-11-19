# DC motor position control

A control system project for regulating the angular position of a direct current (DC) motor using different controllers.

Initially, the practical aspects of constructing the physical experiment are presented, and then digital proportional-integral-derivative (PID), proportional-resonant (PR), and repetitive controllers are implemented.

The following programs are available:
- [Relay method]
- [PID controller]
- [PR controller]
- [Repetitive controller]

##

Let $r(t)$ be the reference of angular position, $y(t)$ the angular position, $u(t)$ the control signal, and $e(t)$ the tacking error. For a PID controller the following response is obtained:
<img width="2953" height="1772" alt="dc_motor_data_pid" src="https://github.com/user-attachments/assets/14285ff0-0643-4f81-ae13-323213615f2c" />

For a PR controller the following response is obtained:
<img width="2953" height="1772" alt="dc_motor_data_pr" src="https://github.com/user-attachments/assets/325b3746-c04a-4fe8-9a6e-0b99bd17af42" />
