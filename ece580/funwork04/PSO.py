import matplotlib.pyplot as plt
import numpy as np
import sys

import numpy as np
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

def getGbest(p0, p1):
    # find the global best from the personal best.
    f = []
    for i in range(len(p0)):
        f.append(func(p0[i], p1[i]))
    gBest = min(f)
    ind = np.argmin(f)
    g0 = p0[ind]
    g1 = p1[ind]

    return gBest, g0, g1

def init(ax, n):
    #n = 100
    x0 = 20* (np.random.rand(n)-0.5)
    x1 = 20* (np.random.rand(n)-0.5)
    # personal best
    p0 = x0
    p1 = x1


    v0 = 0.1*np.random.rand(n)
    v1 = 0.1*np.random.rand(n)
    gBest, g0, g1 = getGbest(p0, p1)
    ax.plot(x0, x1, 'or')
    pBest = []
    for i in range(n):
        pBest.append(func(x0[i], x1[i]))
    return x0, x1, v0, v1, p0,p1,pBest, g0, g1, gBest

def getBestPlot(x0_dec, x1_dec):

    f = []
    for i in range(len(x0_dec)):
        f.append(func(x0_dec[i], x1_dec[i]))
    best = min(f)
    worst = max(f)
    ave = np.mean(f)
    ind = np.argmin(f)
    return ind, best, worst, ave




def pmo(ax):
    n =50
    c1 = 2.01
    c2 = 2.09

    bestList = []
    worstList = []
    aveList = []
    counter = []
    x0, x1, v0, v1, p0,p1,pBest,  g0, g1, gBest  = init(ax, n )

    k = 0.729


    for i in range(20):

        r0 = np.random.rand(n)
        r1 = np.random.rand(n)
        s0 = np.random.rand(n)
        s1 = np.random.rand(n)
        for j in range(n):
            v0[j] = k*(v0[j] + c1*r0[j]*(p0[j]-x0[j])+ c2*s0[j]*(g0-x0[j]))
            v1[j] = k*(v1[j] + c1*r1[j]*(p1[j]-x1[j])+ c2*s1[j]*(g1-x1[j]))
            x0[j] = x0[j] + v0[j]
            x1[j] = x1[j] + v1[j]
            val = func(x0[j], x1[j])
            if val<= pBest[j]:
                pBest[j] = val
                p0[j] = x0[j]
                p1[j] = x1[j]


        gCurrBest, g0Curr, g1Curr = getGbest(p0, p1)
        #print g0Curr, g1Curr,gCurrBest, func(g0Curr, g1Curr)
        if gCurrBest < gBest:
            gBest = gCurrBest
            g0 = g0Curr
            g1 = g1Curr
            print "gBest", g0, g1, gBest, func(g0, g1)

        ind, best, worst, ave  = getBestPlot(x0, x1)
        counter.append(i+1)
        bestList.append(best)
        worstList.append(worst)
        aveList.append(ave)


    ax.plot(x0, x1, "*b")
    fig2 = plt.figure()
    ax1 = fig2.add_subplot(111)
    ax1.plot(counter, bestList, '-o',label='best')
    ax1.plot(counter, aveList, '-*', label = 'average')
    ax1.plot(counter, worstList, '--', label='worst')
    ax1.set_xlabel("Generations")
    ax1.set_ylabel("Objective Function Value")
    ax1.set_title("PSO algorithm")
    ax1.legend()
    plt.show()





def main():
    f, (ax) = plt.subplots(1,1, sharex=False)
    plotContour(ax, [-10,10] , [-10,10])
    pmo(ax)
    plt.show()


if  __name__ == "__main__":
    main()

