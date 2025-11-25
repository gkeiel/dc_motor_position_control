import os, pandas, numpy
import matplotlib.pyplot as plt
os.chdir(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))


# load data
data_pid = pandas.read_csv('dc_motor_position_control_pid/data.csv')
data_pr  = pandas.read_csv('dc_motor_position_control_pr/data.csv')
data_rep = pandas.read_csv('dc_motor_position_control_repetitive/data.csv')
fs = 1/0.002    # sampling frequency
N  = 10000
t  = numpy.arange(N)/fs

e_pid = data_pid['Channel 3'].to_numpy()
e_pr  =  data_pr['Channel 3'].to_numpy()
e_rep = data_rep['Channel 3'].to_numpy()
rmse_pid = numpy.sqrt( (e_pid[5000:N]**2).mean() )
rmse_pr  = numpy.sqrt( (e_pr[5000:N]**2).mean() )
rmse_rep = numpy.sqrt( (e_rep[5000:N]**2).mean() )

# plot data
plt.figure(figsize=(10, 6))
plt.plot(t, e_pid[:N], label=f'PID RMSE={rmse_pid:.2f}')
plt.plot(t, e_pr[:N], label=f'PR_RMSE={rmse_pr:.2f}')
plt.plot(t, e_rep[:N], label=f'repetitive_RMSE={rmse_rep:.2f}')
plt.grid(True)
plt.ylim([-100, 100])
plt.xlim([0, 20])
plt.title('Results for each controller')
plt.xlabel('Time (s)')
plt.ylabel('Signals')
plt.legend()

# save figure
plt.tight_layout()
plt.savefig('dc_motor_data_comparison.png', dpi=300)
plt.show()