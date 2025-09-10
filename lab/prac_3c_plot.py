import matplotlib.pyplot as plt

n_values = [2, 4, 5, 10, 20, 40, 50, 75, 100, 200]
time_taken = [0.000009, 0.000028, 0.000105, 0.000734, 0.007433,
              0.051558, 0.038351, 0.246844, 0.234308, 1.692401]
plt.plot(n_values, time_taken, marker="o")
plt.title("Matrix Multiplication (Strassen) Time Complexity")
plt.xlabel("Size of matrix (n)")
plt.ylabel("Time taken (seconds)")
plt.grid(True)
plt.show()
