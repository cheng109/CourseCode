A = rand(10); 


e = abs(eig(A) )
lamda = max(e)
maxit = 1000; 
[L, U, P] = lu(A); 
x= rand(10,1); 
diff = zeros(maxit,1); 
iter = zeros(maxit,1); 
for i = 1: maxit 
    x = U\(L\(P*x)); 
    x = x/norm(x); 
    lam = x'*A*x ; 
    diff(i) = abs(lam -lamda); 
    iter(i) = i; 
end


plot(iter, diff, 'o-') ; 
xlabel('Iterations'); 
ylabel('Difference'); 


%% 
dim = 4; 
A = rand(dim); 

e = abs(eig(A))
[V, D]  = eig(A)
lamda = max(e)
maxit = 40; 
true_X = V(:,1) 
x= rand(dim,1); 
diff = zeros(maxit,1); 
iter = zeros(maxit,1); 
eps = zeros(maxit,1); 
for i = 1: maxit 
    x = A*x; 
    x = x/norm(x); 
    lam = x'*A*x ; 
    diff(i) = abs(lam -lamda); 
    iter(i) = i; 
    
end


plot(iter, diff, 'o-') ; 
xlabel('Iterations'); 
ylabel('Difference'); 



%%  Problem 2.4
clear; 
clc; 
maxit = 20; 
dim = 6; 
A = rand(dim); 
A = A'*A; 
e = abs(eig(A)); 
lamda = max(e); 
[V, D]  = eig(A); 
true_X = V(:,1) ; 
true_X = true_X/norm(true_X); 

x= rand(dim,1);
x= x/norm(x); 
lam = x'*A*x; 
diff = zeros(maxit,1); 
iter = zeros(maxit,1); 
eps = zeros(maxit,1); 


for i=1:maxit
    x=(A-lam*eye(size(A,1)))\x; 
    x = x/norm(x,2); 
    lam = x'*A*x; 
    diff(i) = norm(lam - lamda);  
    iter(i) = i; 
end

semilogy(iter, diff, 'o-') ; 
xlabel('Iterations'); 
ylabel('Difference'); 



%% problem3_5 
load('purdue_web.mat'); 
n= size(P, 1); 
v = ones(n,1)./n; 
e = ones(n,1); 
alpha = 0.85; 
x = v; 
lam = zeros(n,1); 
iter = zeros(n,1); 
maxit = 10000; 
for i = 1:maxit
    x = (alpha*P + (1-alpha)*v*e')*x;  
    lam(i) = x; 
    iter(i) = i; 
end
plot(iter, lam, '-o') 
