import os, pandas, numpy
import matplotlib.pyplot as plt
os.chdir(os.path.dirname(os.path.abspath(__file__)))


# load data
data = pandas.read_csv('data.csv')
fs = 1/0.002    # sampling frequency
N  = len(data)
t  = numpy.arange(N)/fs
r  = data['Channel 1'].to_numpy()
y  = data['Channel 2'].to_numpy()
e  = data['Channel 3'].to_numpy()
u  = data['Channel 4'].to_numpy()

# plot data
plt.figure(figsize=(10, 6))
plt.plot(t, r, label='r(t) [º]')
plt.plot(t, y, label='y(t) [º]')
plt.plot(t, u, label='u(t) [%]')
plt.plot(t, e, label='e(t) [º]')
plt.grid(True)
plt.ylim([-100, 100])
plt.xlim([0, 20])
plt.title('Results for repetitive controller')
plt.xlabel('Time (s)')
plt.ylabel('Signals')
plt.legend()

# save figure
plt.tight_layout()
plt.savefig('dc_motor_data_repetitive.png', dpi=300)
plt.show()