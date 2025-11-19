clc; clear; close all;

% load data
data = readtable('data.csv');
fs = 1/0.002;
N  = size(data,1);
t  = (0:N-1)/fs;
r  = data.Channel1;
y  = data.Channel2;
e  = data.Channel3;
u  = data.Channel4;

% plot data
figure()
plot(t,r)
hold on
plot(t,y)
plot(t,u)
plot(t,e)
grid on;
ylim([-100 100])
legend('r(t)','y(t)','u(t)','e(t)');

% save data
set(gcf,'PaperUnits','centimeters');
set(gcf,'PaperPosition',[0 0 25 15]);
print(gcf, 'dc_motor_data_pr.png', '-dpng', '-r300');