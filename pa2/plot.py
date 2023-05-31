import matplotlib.pyplot as plt
import numpy as np


x = np.array([1, 2, 3, 4, 5, 6, 7, 8, 9, 10])
y = np.array([0.015, 0.018, 0.021, 0.023, 0.019, 0.025, 0.027, 0.028, 0.030, 0.031])


a, b = np.polyfit(x, y, 1)
plt.scatter(x, y)

plt.plot(x, a*x+b)        
plt.show()