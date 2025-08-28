import matplotlib.pyplot as plt

n_values = [100, 200, 400, 500, 1000, 2000,
            4000, 5000, 10000, 20000]
time_taken = [0.000011, 0.000028, 0.000101, 0.000178, 0.000393,
              0.002455, 0.005398, 0.008287, 0.020927, 0.068689]
plt.plot(n_values, time_taken, marker="o")
plt.title("Bubble Sort Time Complexity")
plt.xlabel("Number of elements (n)")
plt.ylabel("Time taken (seconds)")
plt.grid(True)
plt.show()
