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
xlabel('Time (s)')
ylabel('Signals')
legend('r(t) [º]','y(t) [º]','u(t) [%]','e(t) [º]');

% save data
set(gcf,'PaperUnits','centimeters');
set(gcf,'PaperPosition',[0 0 25 15]);
print(gcf, 'dc_motor_data_repetitive.png', '-dpng', '-r300');