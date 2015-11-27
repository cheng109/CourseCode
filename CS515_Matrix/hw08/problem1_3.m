
n = 10; 
on = ones(n,1); 
A = spdiags([-2*on 4*on -2*on],-1:1,n,n); 
A = full(A) 
lam = eig(A); 
plotDisk(A); 