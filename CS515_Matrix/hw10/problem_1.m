cd /Users/cheng109/work/CourseCode/CS515_Matrix/hw10; 

load poisson2D
A=Problem.A; 
b=Problem.b; 
A= (A+A')/2; 
sigma = 1.7e-2; 
tol = 1.0e-8; 
[n,m] = size(A); 
maxit = 100; 
restart = 20; 
A = A-sigma*eye(n); 
res_1 = zeros(maxit, 1); 
res_2 = zeros(maxit, 1); 


%[L,U] = ilu(sparse(A),struct('type','ilutp','droptol',1e-5));
L = ichol(sparse(A)); 
for i=1:maxit
    %[x,flag,res_2(i),iter] = gmres(A,b,restart,tol,i,L, U); 
    %[x,flag,res_2(i),iter] = gmres(A,b,restart,tol,i,L);
    res_2(i)
end

[x,flag,res,iter] = gmres(A,b,restart,tol,100000,L);
i=1:maxit; 
semilogy(i, res_2); %, i, res_2, '-*', 'o-'); 
xlabel('Number of iterations'); 
ylabel('Residual'); 
title('GMRES'); 


%% problem_1
for i=1:maxit  
    [x, flag, res_1(i), iter] = minres(A,b,tol,i); 
end

for i=1:maxit
    [x,flag,res_2(i),iter] = gmres(A,b,restart,tol,i); 
end

i=1:maxit; 

semilogy(i, res_1) ; 
semilogy(i, res_2); %, i, res_2, '-*', 'o-'); 
xlabel('Number of iterations'); 
ylabel('Residual'); 
title('GMRES'); 





