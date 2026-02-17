def PlotPoly():
    fid = open("poly.data", "r")
    NumPts = 0
    while True:
        line = fid.readline()
        if not line:
            break
        NumPts += 1
    fid.close()

    import numpy as np
    import matplotlib.pyplot as plt

    x = np.zeros(NumPts, dtype=float)
    y = np.zeros(NumPts, dtype=float)
    fid = open("poly.data", "r")
    for k in range(NumPts):
        linestring = fid.readline()
        linelist = linestring.split()
        x[k] = float(linelist[0])
        y[k] = float(linelist[1])
    fid.close()

    plt.figure(1)
    plt.plot(x, y, marker="o", linewidth=1)
    plt.xlim(-1.0, 1.0)
    ax = plt.gca()
    ax.grid(True)
    plt.xlabel("x-axis")
    plt.ylabel("y-axis")
    plt.title("Chebyshev Polynomial Plot")
    plt.savefig("chebyshev.png", dpi=300, bbox_inches="tight")
    plt.show()

if __name__ == "__main__":
    PlotPoly()
