clc; clear;

% gain tuning
k_u = 231.5;
P_u = 0.04;
w_u = 2*pi*(1/P_u);
w_r = 0.628;
r_p = -0.4;
i_p = 0.08;

k_p = k_u*r_p*(w_r^2 -w_u^2)/w_u^2
k_r = k_u*i_p*(w_u^2 -w_r^2)/w_u

% coefficients
k_p = k_p/100;
k_r = k_r/1000;
omega = 2*pi*0.1;
xi    = 0.001;
alpha = omega/tan(omega*0.002/2.0);

b_0 = 4.0*k_p*alpha*alpha +4.0*k_p*alpha*omega*xi +k_r*alpha*omega*xi +k_r*omega*omega;
b_1 = -8.0*k_p*alpha*alpha +2.0*k_r*omega*omega; 
b_2 = 4.0*k_p*alpha*alpha -4.0*k_p*alpha*omega*xi -k_r*alpha*omega*xi +k_r*omega*omega;
a_0 = alpha*alpha +2.0*alpha*omega*xi +omega*omega;
a_1 = -2.0*alpha*alpha +2.0*omega*omega;
a_2 = alpha*alpha -2.0*alpha*omega*xi +omega*omega;

c_1 = b_0/a_0
c_2 = b_1/a_0
c_3 = b_2/a_0
c_4 = a_1/a_0
c_5 = a_2/a_0
