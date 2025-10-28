import matplotlib.pyplot as plt
import numpy as np

n = [1, 2, 5, 10, 15, 20, 25, 30, 35, 40, 45, 50]
t1 = [0.000002, 0.000001, 0.000001, 0.000002, 0.000004, 0.000027,
      0.000303, 0.003314, 0.036006, 0.363289, 4.078728, 46.813421]
t2 = [0.000001, 0.000001, 0.000001, 0.000000, 0.000000, 0.000000,
      0.000000, 0.000001, 0.000000, 0.000001, 0.000001, 0.000000]
t3 = [0.000003, 0.000001, 0.000001, 0.000002, 0.000001, 0.000001,
      0.000002, 0.000001, 0.000001, 0.000002, 0.000002, 0.000002]
t4 = [0.000000, 0.000000, 0.000000, 0.000001, 0.000001, 0.000001,
      0.000001, 0.000000, 0.000001, 0.000000, 0.000000, 0.000000]

x = np.linspace(1, 8, 8)
k = 0.004
plt.plot(n, t1, label="Recursive", marker="o")
plt.plot(n, t2, label="Iterative", marker="o")
plt.plot(n, t3, label="Memoization", marker="o")
plt.plot(n, t4, label="Formulation", marker="o")

plt.title("Fibonacci Series (All) Time Complexity")
plt.xlabel("nth Term (n)")
plt.ylabel("Time taken (seconds)")
plt.grid(True)
plt.legend()
plt.show()
