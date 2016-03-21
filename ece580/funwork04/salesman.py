
import matplotlib.pyplot as plt
import numpy as np

def getDist(locX, locY):
    dist = 0
    for i in range(len(locX)-1):
        dx = locX[i]-locX[i+1]
        dy = locY[i]-locY[i+1]

        dist += np.sqrt(dx**2+dy**2)

    dist += np.sqrt((locX[-1]-locX[0])**2 + (locY[-1]-locY[0])**2)

    return dist

def plotConnection(locX, locY):
    for i in range(len(locX)-1):
        plt.plot((locX[i], locX[i+1]), (locY[i], locY[i+1]), 'o-b')
    plt.plot((locX[0], locX[-1]), (locY[0], locY[-1]), 'o-b')
    plt.xlabel("Location X")
    plt.ylabel("Location Y")
    plt.title("Traveling Salesman Problem")
    plt.show()



def main():

    locX = [7.7176, 9.8397, 1.3001, 4.6141, 9.0204, 1.5651, 6.4311,
            8.0298, 8.2941, 0.6621, 9.6546, 6.8045, 8.0196, 8.1590, 8.0531]
    locY = [0.8955, 9.8352, 7.7070, 0.0784, 4.8838, 3.3703, 6.1604,
            5.5397, 1.2147, 2.5383, 0.5923, 9.2022, 2.8386, 7.1041, 1.8498]


    print getDist(locX, locY)
    plotConnection(locX, locY)
    return "hello"


if __name__=="__main__":
    main()