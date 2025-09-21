import matplotlib.pyplot as plt
import numpy as np
import math

n = [1, 2, 3, 4, 5, 6, 7, 8]
t1 = [0.000001, 0.000002, 0.000003, 0.000013,
      0.000084, 0.000671, 0.003226, 0.029327]
t2 = [0.000008, 0.000020, 0.000100, 0.000707,
      0.004184, 0.034965, 0.246129, 2.070637]
t3 = [0.000003, 0.000018, 0.000131, 0.000505,
      0.003828, 0.026499, 0.184726, 1.328793]

x = np.linspace(1, 8, 8)
k = 0.004
plt.plot(n, t1, label="Iterative", marker="o")
plt.plot(n, t2, label="Divide & Conquer", marker="o")
plt.plot(n, t3, label="Strassen", marker="o")

plt.plot(x, k*x**3, label='O(n^3)', linestyle="--")
plt.plot(x, k*x**(math.log2(7)), label='O(n^2.81)', linestyle="--")

plt.title("Matrix Multiplication (All) Time Complexity")
plt.xlabel("Size of matrix (n)")
plt.ylabel("Time taken (seconds)")
plt.grid(True)
plt.legend()
plt.show()
