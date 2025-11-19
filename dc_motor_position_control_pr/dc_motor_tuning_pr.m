clc; clear;

k_u = 181.89;
w_u = 31.416;
w_r = 0.628;
r_p = -0.4;
i_p = 0.08;

k_r = k_u*i_p*(w_u^2 -w_r^2)/w_u
k_p = k_u*r_p*(w_r^2 -w_u^2)/w_u^2

