import matplotlib.pyplot as plt

n_values = [100, 200, 400, 500, 1000, 2000,
            4000, 5000, 10000, 20000]
time_taken = [0.000044, 0.000153, 0.000677, 0.001104, 0.003078,
              0.009419, 0.022273, 0.029047, 0.093074, 0.372658]
plt.plot(n_values, time_taken, marker="o")
plt.title("Quick Sort Time Complexity")
plt.xlabel("Number of elements (n)")
plt.ylabel("Time taken (seconds)")
plt.grid(True)
plt.show()
