import matplotlib.pyplot as plt

n_values = [100, 200, 400, 500, 1000, 2000,
            4000, 5000, 10000, 20000]
time_taken = [0.000014, 0.000033, 0.000069, 0.000069, 0.000126,
              0.000189, 0.000299, 0.000371, 0.000657, 0.001328]
plt.plot(n_values, time_taken, marker="o")
plt.title("Merge Sort Time Complexity")
plt.xlabel("Number of elements (n)")
plt.ylabel("Time taken (seconds)")
plt.grid(True)
plt.show()
