import numpy as np
import random 
from mayavi import mlab
from matplotlib import colors
def plotProblem5(): 
    x = []
    y = []
    z = []
    f=[]
    for i in range(500000): 
        x1 = random.uniform(-1,1)
        t1 = (2*np.random.binomial(1, 0.5)-1) # t1 is randomly assigned as -1 or 1
        t2 = (2*np.random.binomial(1, 0.5)-1) # t1 is randomly assigned as -1 or 1
        x2 = t2*(1-abs(x1))
        if(abs(x1)<abs(x2)) :
            x3 = random.uniform (-x1, x1)
        else :
            x3 = random.uniform (-x2, x2)
        #print x1, x3, x3
        x.append(x1)
        y.append(x2)
        z.append(x3)
        f.append(2.0)
    
    mlab.points3d(x,y,z, scale_factor=0.01, color=colors.colorConverter.to_rgb('r'))
    mlab.points3d(z,x,y, color=colors.colorConverter.to_rgb('g'))
    mlab.points3d(y,z,x, color=colors.colorConverter.to_rgb('b'))

        
    
    mlab.show()
    
        
            
    


plotProblem5()