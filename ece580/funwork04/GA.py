import matplotlib.pyplot as plt
import numpy as np
def func(x1, x2):
    return 20 + 0.01*x1**2 + 0.01*x2**2 \
           - 10*(np.cos(0.2*np.pi*x1)+np.cos(0.2*np.pi*x2))


def plotContour(ax, xlim, ylim):
    delta = 0.1
    x = np.arange(xlim[0], xlim[1], delta)
    y = np.arange(ylim[0], ylim[1], delta)
    X1, X2 = np.meshgrid(x, y)
    Z = func(X1,X2)
    ax.set_title("Rastrgin Function")
    ax.set_xlabel("X1")
    ax.set_ylabel("X2")
    cs = ax.contour(X1, X2, Z)
    return cs


def mapping(binNum, n):

    decVal = 20.0 * binNum/(np.power(2, n-1)) -10

    return decVal


def init(ax, n):
    L = 32
    max = np.power(2, L/2-1)
    x0 = np.random.rand(n)*max
    x1 = np.random.rand(n)*max
    for i in range(n):
        x0[i] = mapping(x0[i], L/2)
        x1[i] = mapping(x1[i], L/2)

    ax.plot(x0, x1, '*')
    return x0, x1

def selection(x0, x1, k):
    f = []

    for i in range(len(x0)):
        f.append(func(x0[i], x1[i]))
    cumSum = np.cumsum(f)
    new_x0 = []
    new_x1 = []
    f_index = [0] * k

    alpha = np.random.rand(k)*sum(f)
    for i in range(k):
        for j in range(len(x0)):
            if alpha[i]> cumSum[j]:
                f_index[i] += 1
            else:
                break
    print f_index

    for index in f_index:
        new_x0.append(x0[f_index[index]])
        new_x1.append(x1[f_index[index]])
    return new_x0, new_x1


def ga(ax):
    n = 20   #  number of initial points.
    L = 32

    x0, x1 = init(ax, n)
    x0, x1 = selection(x0, x1, k=len(x0))



def main():
    f, (ax) = plt.subplots(1,1, sharex=False)
    plotContour(ax, [-10,10] , [-10,10])
    ga(ax)
    plt.show()

if  __name__ == "__main__":
    main()


