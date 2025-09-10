import matplotlib.pyplot as plt

n_values = [2, 4, 8, 20, 30, 50, 100, 150, 250, 500]
time_taken = [0.000001, 0.000001, 0.000007, 0.000023, 0.000070,
              0.000418, 0.0001687, 0.007553, 0.023794, 0.188353]
plt.plot(n_values, time_taken, marker="o")
plt.title("Matrix Multiplication (Iterative) Time Complexity")
plt.xlabel("Size of matrix (n)")
plt.ylabel("Time taken (seconds)")
plt.grid(True)
plt.show()
