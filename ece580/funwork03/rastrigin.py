
import matplotlib.pyplot as plt

import numpy as np
def rastriginFunc(x1, x2):
    return 20 + 0.01*x1**2 + 0.01*x2**2 \
           - 10*(np.cos(0.2*np.pi*x1)+np.cos(0.2*np.pi*x2))


def plotContour():
    delta = 0.1
    lim = 20
    x = np.arange(-lim, lim, delta)
    y = np.arange(-lim, lim, delta)
    X1, X2 = np.meshgrid(x, y)
    Z = rastriginFunc(X1,X2)
    plt.figure()
    plt.title("Rastrgin Function")
    plt.xlabel("X1")
    plt.ylabel("Y1")
    cs = plt.contour(X1, X2, Z)
    #plt.show()
    return cs

def gradientRastrigin(x1, x2):
    # df/dx1:
    g1 = 0.02*x1 +2*np.pi*np.sin(0.2*np.pi*x1)
    g2 = 0.02*x2 +2*np.pi*np.sin(0.2*np.pi*x2)
    return g1, g2

def lineSearchFunc(X, alpha):
    x1, x2 = X
    g1, g2 = gradientRastrigin(x1, x2)
    return rastriginFunc(x1-alpha*g1, x2-alpha*g2)


def goldenSection(func,X,  a,b,c, tol):
    rho = (1+np.sqrt(5))/2  # 1.618
    if abs(a-b) < tol:
        return (a+b)/2
    d = c+ (2-rho)*(b-c)
    if func(X, d) < func(X, c):
        return goldenSection(func, X,  c, d, b,tol)
    else:
        return goldenSection(func, X,  d, c, a, tol)


def steepesDescent():

    X0 = (7.5, 9.0)
    diff = 1.0
    x1_current = X0[0]
    x2_current = X0[1]
    while diff > 1.0e-6:
        g1, g2 = gradientRastrigin(x1_current, x2_current)
        alpha = goldenSection(lineSearchFunc, 0, 1, 0.4, 1.0e-6)
        x1_next = x1_current - alpha * g1
        x2_next = x2_current - alpha * g2



def main():
    #cs = plotContour()
    #plt.show()
    # testLineSearchFunction
    X0= (7.5, 9.0)
    alpha = []
    func = []
    for i in np.arange(-10, 10, 0.1):
        alpha.append(i)
        func.append(lineSearchFunc(X0, i))
    plt.plot(alpha, func, '-')
    plt.xlabel(r"$\alpha$")
    plt.ylabel(r"$f(x-\alpha*g)$")
    plt.show()




if  __name__ == "__main__":
    main()