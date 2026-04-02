import numpy as np
import matplotlib.pyplot as plt

# plot V(x0)
data1 = np.loadtxt("potential.data")
x0 = data1[:, 0]
V = data1[:, 1]

plt.figure(figsize=(7, 5))
plt.plot(x0, V, linewidth=2)
plt.xlabel("x0")
plt.ylabel("V(x0)")
plt.title("1D Electrostatic Potential")
plt.grid(True)
plt.tight_layout()
plt.savefig("potential.png", dpi=300)

# plot J0(x)
data2 = np.loadtxt("bessel.data")
x = data2[:, 0]
j0 = data2[:, 1]

plt.figure(figsize=(7, 5))
plt.plot(x, j0, linewidth=2)
plt.xlabel("x")
plt.ylabel("J0(x)")
plt.title("Bessel Function J0(x)")
plt.grid(True)
plt.tight_layout()
plt.savefig("bessel.png", dpi=300)

plt.show()