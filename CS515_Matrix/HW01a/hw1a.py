import numpy as np
from numpy.linalg import matrix_rank

#  problem #1
a = np.dot([[1,1,2],[3,5,8], [13,21,34]], [[1,-2,3], [-4, 5, -6], [7, -8, 9]])
#print(a)

x = np.ones(1000)
y=np.arange(1., 1001.)
print (np.dot(x, y))

n=6
N=10000
C =np.zeros((n,)*2)
for i in range(N):
    x = np.random.randn(n,1)
    y = np.random.randn(n,1)
    C+=np.dot(x, np.transpose(y))
C = C/N
print(matrix_rank(C))

