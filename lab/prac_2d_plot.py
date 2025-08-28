import matplotlib.pyplot as plt

n_values = [100, 200, 400, 500, 1000, 2000,
            4000, 5000, 10000, 20000]
time_taken = [0.000037, 0.000110, 0.000330, 0.000469, 0.001713,
              0.005180, 0.014430, 0.018078, 0.044199, 0.148808]
plt.plot(n_values, time_taken, marker="o")
plt.title("Selection Sort Time Complexity")
plt.xlabel("Number of elements (n)")
plt.ylabel("Time taken (seconds)")
plt.grid(True)
plt.show()
