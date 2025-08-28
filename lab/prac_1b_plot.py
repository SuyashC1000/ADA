import matplotlib.pyplot as plt

n_values = [1000, 2000, 4000, 5000, 10000, 20000,
            40000, 50000, 100000, 200000]
time_taken = [0.000030, 0.000033, 0.000039, 0.000040, 0.000044,
              0.000052, 0.000047, 0.000054, 0.000056, 0.000061]
plt.plot(n_values, time_taken, marker="o")
plt.title("Binary Search Time Complexity")
plt.xlabel("Number of elements (n)")
plt.ylabel("Time taken (milliseconds)")
plt.grid(True)
plt.show()
