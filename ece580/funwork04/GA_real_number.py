import matplotlib.pyplot as plt
import numpy as np
from random import sample
def func(x1, x2):
    return -20 - 0.01*x1**2 - 0.01*x2**2 \
           + 10*(np.cos(0.2*np.pi*x1)+np.cos(0.2*np.pi*x2))


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
    x0_dec = []
    x1_dec = []
    L = 32
    max = np.power(2, L/2-1)
    x0_bin = np.random.randint(0, max, size=n)
    x1_bin = np.random.randint(0, max, size=n)
    for i in range(n):
        x0_dec.append(mapping(x0_bin[i], L/2))
        x1_dec.append(mapping(x1_bin[i], L/2))

    ax.plot(x0_dec, x1_dec, 'ob')
    return x0_bin, x1_bin, x0_dec, x1_dec

def selection(x0_dec, x1_dec, k):
    f = []
    for i in range(len(x0_dec)):
        f.append(func(x0_dec[i], x1_dec[i]))
    base = min(f)
    f = [x-base for x in f]
    cumSum = np.cumsum(f)
    new_x0_dec = []
    new_x1_dec = []
    #new_x0_bin = []
    #new_x1_bin = []
    f_index = [0] * k


    alpha = np.random.rand(k)*sum(f)
    for i in range(k):
        for j in range(len(x0_dec)):
            if alpha[i]> cumSum[j]:
                f_index[i] += 1
            else:

                break

    for index in f_index:
        new_x0_dec.append(x0_dec[f_index[index]])
        new_x1_dec.append(x1_dec[f_index[index]])
        #new_x0_bin.append(x0_bin[f_index[index]])
        #new_x1_bin.append(x1_bin[f_index[index]])
    return  new_x0_dec, new_x1_dec


def crossover(x0_dec, x1_dec, n):

    pc = 0.65
    pm = 0.075

    # choosing crossing site;
    N = 2* int(pc *  n/2)   #  number of parents who are ready to do crossover.
    L = 32
    parent_index =  sample(xrange(len(x0_dec)), N)
    i=0
    while i<len(parent_index):
        parent1_x0 = x0_dec[parent_index[i]]
        parent1_x1 = x1_dec[parent_index[i]]
        parent2_x0 = x0_dec[parent_index[i+1]]
        parent2_x1 = x1_dec[parent_index[i+1]]

        w = np.random.normal(0, 0.1, 4)
        child1_x0  = (parent1_x0+parent2_x0)/2 + w[0]
        child1_x1  = (parent1_x1+parent2_x1)/2 + w[1]
        child2_x0  = (parent1_x0+parent2_x0)/2 + w[2]
        child2_x1  = (parent1_x1+parent2_x1)/2 + w[3]

        x0_dec[parent_index[i]] = child1_x0
        x1_dec[parent_index[i]] = child1_x1
        x0_dec[parent_index[i+1]] = child2_x0
        x1_dec[parent_index[i+1]] = child2_x1


        i+=2


    ## Mutation
    for i in range(len(x0_dec)):
        val = np.random.rand()

        if val < pm :
            w = np.random.normal(0, 0.1, 2)
            x0_dec[i] += w[0]
            x1_dec[i] += w[1]



    return  x0_dec, x1_dec


def ga(ax):
    n = 50   #  number of initial points.
    L = 32

    x0_bin, x1_bin, x0_dec, x1_dec = init(ax, n)

    for iter in range(50):
        x0_dec, x1_dec = selection(x0_dec, x1_dec, k=len(x0_dec))
        x0_dec, x1_dec = crossover(x0_dec, x1_dec, n)  # crossover and mutation

    plt.plot(x0_dec, x1_dec, '*r')

def main():
    f, (ax) = plt.subplots(1,1, sharex=False)
    plotContour(ax, [-10,10] , [-10,10])
    ga(ax)
    plt.show()

if  __name__ == "__main__":
    main()


