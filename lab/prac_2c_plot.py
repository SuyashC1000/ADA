import matplotlib.pyplot as plt

n_values = [100, 200, 400, 500, 1000, 2000,
            4000, 5000, 10000, 20000]
time_taken = [0.000003, 0.000007, 0.000024, 0.000036, 0.000129,
              0.000433, 0.001973, 0.002386, 0.007846, 0.020464]
plt.plot(n_values, time_taken, marker="o")
plt.title("Insertion Sort Time Complexity")
plt.xlabel("Number of elements (n)")
plt.ylabel("Time taken (seconds)")
plt.grid(True)
plt.show()
