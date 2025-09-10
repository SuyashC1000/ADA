import matplotlib.pyplot as plt

n_values = [2, 4, 6, 8, 20, 30, 50, 75, 125, 250]
time_taken = [0.000008, 0.000019, 0.000142, 0.000125, 0.005645,
              0.008010, 0.044485, 0.342079, 0.328072, 2.568153]
plt.plot(n_values, time_taken, marker="o")
plt.title("Matrix Multiplication (Divide & Conquer) Time Complexity")
plt.xlabel("Size of matrix (n)")
plt.ylabel("Time taken (seconds)")
plt.grid(True)
plt.show()
