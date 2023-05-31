import matplotlib.pyplot as plt
import numpy as np


x = np.array([1, 2, 3, 4, 5, 6, 7, 8, 9, 10])
y = np.array([0.004, 0.006, 0.006, 0.007, 0.008, 0.009, 0.008, 0.011, 0.012, 0.013])


a, b = np.polyfit(x, y, 1)
plt.scatter(x, y)

plt.plot(x, a*x+b)        
plt.show()