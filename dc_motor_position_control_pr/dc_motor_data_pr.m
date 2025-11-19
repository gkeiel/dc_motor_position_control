clc; clear; close all

data = readtable('data.csv');
fs = 1/0.002;
N  = size(data,1);
t  = (0:N-1)/fs;
r  = data.Channel1;
y  = data.Channel2;
e  = data.Channel3;
u  = data.Channel4;

figure()
plot(t,r)
hold on
plot(t,y)
plot(t,e)
plot(t,u)
grid on;
legend('r(t)','y(t)','e(t)','u(t)');