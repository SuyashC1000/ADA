import matplotlib.pyplot as plt

n = [1, 2, 5, 10, 20, 40, 75, 100, 200, 400]
t1 = [0.000001, 0.000001, 0.000002, 0.000002, 0.000002,
      0.000003, 0.000006, 0.000008, 0.000016, 0.000042]
t2 = [0.000001, 0.000000, 0.000001, 0.000004, 0.000010,
      0.000041, 0.000124, 0.000215, 0.000858, 0.002208]

plt.plot(n, t1, label="Dreedy", marker="o")
plt.plot(n, t2, label="Dynamic", marker="o")

plt.title("Knapsack Problem (All) Time Complexity")
plt.xlabel("nth Items (n)")
plt.ylabel("Time taken (seconds)")
plt.grid(True)
plt.legend()
plt.show()
