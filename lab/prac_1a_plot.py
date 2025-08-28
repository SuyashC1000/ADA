import matplotlib.pyplot as plt

n_values = [1000, 2000, 4000, 5000, 10000, 20000,
            40000, 50000, 100000, 200000]
time_taken = [0.000001, 0.000002, 0.0000004, 0.000005, 0.000006,
              0.000013, 0.000027, 0.000034, 0.000076, 0.000109]
plt.plot(n_values, time_taken, marker="o")
plt.title("Linear Search Time Complexity")
plt.xlabel("Number of elements (n)")
plt.ylabel("Time taken (seconds)")
plt.grid(True)
plt.show()
