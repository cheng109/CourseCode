
import matplotlib.pyplot as plt
import numpy as np
import random
from random import shuffle
import sys

def getDist(comb):
    locX = zip(*comb)[0]
    locY = zip(*comb)[1]
    dist = 0
    for i in range(len(locX)-1):
        dx = locX[i]-locX[i+1]
        dy = locY[i]-locY[i+1]

        dist += np.sqrt(dx**2+dy**2)

    dist += np.sqrt((locX[-1]-locX[0])**2 + (locY[-1]-locY[0])**2)

    return dist

def plotConnection(comb):
    locX = zip(*comb)[0]
    locY = zip(*comb)[1]
    for i in range(len(locX)-1):
        plt.plot((locX[i], locX[i+1]), (locY[i], locY[i+1]), 'o-b')
    plt.plot((locX[0], locX[-1]), (locY[0], locY[-1]), 'o-b')
    plt.xlabel("Location X")
    plt.ylabel("Location Y")
    plt.title("Traveling Salesman Problem")
    plt.show()


def switchByIndex(ind1, ind2, List):
    temp = List[ind2]
    List[ind2] = List[ind1]
    List[ind1] = temp

    return List

def init(locX, locY, num):
    zList = []
    for i in range(num):
        z = zip(locX, locY)
        shuffle(z)
        zList.append(z)


    return zList

def listInsert(l, l1,  pivot):
    # insert l1 into l starting from pivot points:
    assert (pivot<len(l))
    new_list = []
    for i in range(pivot):
        new_list.append(l[i])

    new_list.extend(l1)
    for i in np.arange(pivot, len(l)):
        new_list.append(l[i])
    return new_list

def findMinComb(zList):
    minD = float("inf")
    ind = 0
    for i in range(len(zList)):
        comb = zList[i]
        if getDist(comb) < minD:
            minD = getDist(comb)
            ind = i
    return i


def selection(zList):
    f = []
    k = len(zList)
    new_zList =[]

    minIndex = findMinComb(zList)
    new_zList.append(zList[minIndex])   # retain the minimum from the previous generation.

    for comb in zList:

        f.append(-getDist(comb))
    base = min(f)
    f = [x-base for x in f]
    cumSum = np.cumsum(f)
    alpha = np.random.rand(k-1)*sum(f)
    f_index = [0]* (k-1)
    for i in range(len(alpha)):
        for j in range(len(cumSum)):
            if alpha[i] > cumSum[j]:
                 f_index[i] += 1
            else:
                break
    #print f_index

    for ind in f_index:
        new_zList.append(zList[ind])

    return new_zList

def crossover(zList):
    pc = 0.75
    N = int(pc*len(zList)/2)*2   # number of  parents (even number)
    numSub = int(len(zList[0])/3)

    parent_index =  random.sample(xrange(len(zList)), N)
    i=0
    while i<len(parent_index):
        pivot1 = random.sample(xrange(1,len(zList[0])*2/3-1), 1)[0]
        pivot2 = random.sample(xrange(1,len(zList[0])*2/3-1), 1)[0]
        #print pivot
        parent1 = zList[parent_index[i]]
        parent2 = zList[parent_index[i+1]]

        snap1 = [x for x in parent2 if x not in parent1[pivot1: pivot1+numSub]]
        snap2 = [x for x in parent1 if x not in parent2[pivot2: pivot2+numSub]]

        zList[parent_index[i]] = listInsert(snap1, parent1[pivot1:pivot1+numSub], pivot1)
        zList[parent_index[i+1]] = listInsert(snap2, parent2[pivot2:pivot2+numSub], pivot2)

        #print zList[parent_index[i]]
        #print zList[parent_index[i+1]]


        i+=2
    return zList

def mutation(zList):

    pm = 0.0075

    #N = int(pc*len(zList))   # number of single parents.

    for i in range(len(zList)):
        m = np.random.rand()
        #print m
        if m<pm:
            pivot = random.sample(xrange(1,len(zList[0])), 2)
            zList[i] = switchByIndex(pivot[0], pivot[1], zList[i])

    return zList



def GA_algorithm(locX, locY):
    num = 50   # initiate 50 combinations

    zList = init(locX, locY, num)

    counter = []
    best = []

    for i in range(1000):
        counter.append(i+1)
        zList = selection(zList)
        zList = crossover(zList)
        zList = mutation(zList)
        bestDist = sys.maxint
        for comb in zList:
            d = getDist(comb)
            if d<bestDist:
                bestDist = d
                bestPath = comb


        best.append(bestDist)
    print bestDist
    plt.plot(counter, best, '-')
    plt.xlabel("Generations")
    plt.ylabel("Distance")
    plt.show()

    plotConnection(bestPath)

    # crossover
    return locX, locY

def main():

    locX = [7.7176, 9.8397, 1.3001, 4.6141, 9.0204, 1.5651, 6.4311,
            8.0298, 8.2941, 0.6621, 9.6546, 6.8045, 8.0196, 8.1590, 8.0531]
    locY = [0.8955, 9.8352, 7.7070, 0.0784, 4.8838, 3.3703, 6.1604,
            5.5397, 1.2147, 2.5383, 0.5923, 9.2022, 2.8386, 7.1041, 1.8498]
    GA_algorithm(locX, locY)





if __name__=="__main__":
    main()