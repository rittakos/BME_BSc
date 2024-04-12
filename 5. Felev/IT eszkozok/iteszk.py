import numpy as np

temps = [-40, 25, 55, 85, 100, 125, 150] # a hőmérsékletek
voltages = [0.779, 0.6583, 0.6007, 0.5456, 0.5164, 0.4673, 0.4175] # a feszültségek
degree = 2 # hányadfokú közelítést akarsz
eq = np.polyfit(temps, voltages, degree)

d = []
for i in range(len(temps)):
	d.append(abs(1000 * (voltages[i] - (eq[0] * temps[i] * temps[i] + eq[1] * temps[i] + eq[2]))))

# print(eq[0] * 1000)

# for i in range(len(temps)):
# 	d.append(abs(1000 * (voltages[i] - (eq[0] * temps[i] + eq[1]))))

print(max(d))