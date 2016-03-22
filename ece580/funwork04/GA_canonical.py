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

def int2bin(val):
    return



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

def selection(x0_bin, x1_bin, x0_dec, x1_dec, k):
    f = []
    for i in range(len(x0_dec)):
        f.append(func(x0_dec[i], x1_dec[i]))
    base = min(f)
    f = [x-base for x in f]
    cumSum = np.cumsum(f)
    new_x0_dec = []
    new_x1_dec = []
    new_x0_bin = []
    new_x1_bin = []
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
        new_x0_bin.append(x0_bin[f_index[index]])
        new_x1_bin.append(x1_bin[f_index[index]])
    return new_x0_bin, new_x1_bin, new_x0_dec, new_x1_dec


def crossover(x0_bin, x1_bin, x0_dec, x1_dec, n):

    pc = 0.65
    pm = 0.0075

    # choosing crossing site;
    N = 2* int(pc *  n/2)   #  number of parents who are ready to do crossover.
    L = 32
    parent_index =  sample(xrange(len(x0_dec)), N)
    i=0
    while i<len(parent_index):
        parent1 = "{0:b}".format( x0_bin[parent_index[i]]*np.power(2, L/2) + x1_bin[parent_index[i]]).zfill(L)
        parent2 = "{0:b}".format( x0_bin[parent_index[i+1]]*np.power(2, L/2)+ x1_bin[parent_index[i+1]]).zfill(L)
        site = np.random.randint(0,L-1)
        child1 = parent1[0:site] + parent2[site:L]
        child2 = parent2[0:site] + parent1[site:L]


        x0_bin[parent_index[i]]  =  int(child1[0:L/2], 2)
        x0_bin[parent_index[i+1]]=  int(child2[L/2:L], 2)
        x1_bin[parent_index[i]]  =  int(child1[L/2:L], 2)
        x1_bin[parent_index[i+1]]=  int(child2[0:L/2], 2)
        i+=2


    ## Mutation
    for i in range(len(x0_bin)):
        s = "{0:b}".format(x0_bin[i]).zfill(L/2)
        new_s = ""
        for j in range(len(s)):
            val = np.random.rand()
            if val < pm:
                new_s += str(1- int(s[j]))
            else:
                new_s += s[j]
        x0_bin[i] = int(new_s, 2)

        s1 = "{0:b}".format(x1_bin[i]).zfill(L/2)
        new_s1 = ""
        for j in range(len(s1)):
            val = np.random.rand()
            if val < pm:
                new_s1 += str(1- int(s1[j]))
            else:
                new_s1 += s1[j]

        x1_bin[i] = int(new_s1, 2)



    #update x0_dec and x1_dec:
    for i in range(len(x0_bin)):
        x0_dec[i]  = mapping(x0_bin[i], L/2)
        x1_dec[i]  = mapping(x1_bin[i], L/2)


    return x0_bin, x1_bin, x0_dec, x1_dec

def getBestPlot(x0_dec, x1_dec):

    f = []
    for i in range(len(x0_dec)):
        f.append(-func(x0_dec[i], x1_dec[i]))
    best = min(f)
    worst = max(f)
    ave = np.mean(f)
    ind = np.argmin(f)
    return ind, best, worst, ave





def ga(ax):
    n = 50   #  number of initial points.
    bestList = []
    worstList = []
    aveList = []
    counter = []

    x0_bin, x1_bin, x0_dec, x1_dec = init(ax, n)

    for i in range(50):
        x0_bin, x1_bin, x0_dec, x1_dec = selection(x0_bin, x1_bin, x0_dec, x1_dec, k=len(x0_dec))
        x0_bin, x1_bin, x0_dec, x1_dec = crossover(x0_bin, x1_bin, x0_dec, x1_dec, n)  # crossover and mutation

        ind, best, worst, ave  = getBestPlot(x0_dec, x1_dec)

        counter.append(i+1)
        bestList.append(best)
        worstList.append(worst)
        aveList.append(ave)

    print x0_dec[ind], x1_dec[ind], -func(x0_dec[ind], x1_dec[ind])

    plt.plot(x0_dec, x1_dec, '*r')

    fig2 = plt.figure()
    ax1 = fig2.add_subplot(111)
    ax1.plot(counter, bestList, '-o',label='best')
    ax1.plot(counter, aveList, '-*', label = 'average')
    ax1.plot(counter, worstList, '--', label='worst')
    ax1.set_xlabel("Generations")
    ax1.set_ylabel("Objective Function Value")
    ax1.set_title("Canonical genetic algorithm")
    ax1.legend()
    plt.show()









def main():
    f, (ax) = plt.subplots(1,1, sharex=False)
    plotContour(ax, [-10,10] , [-10,10])
    ga(ax)
    plt.show()

if  __name__ == "__main__":
    main()


