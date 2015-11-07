function lambda = RayleighQuotient(m)
% lambda = RayleighQuotient(m)
% This script illustrates the convergence of 
% shifted inverse iteration and
% Rayleigh quotient iteration.
% The input m defines the size of the symmetric
% random matrix to be used.
% The function returns a vector lambda of iterates 
% computed by the Rayleigh quotient iteration.
clc
disp(sprintf('Finding eigenvalue of symmetric matrix of size %d', m))
% A parameter to estimate when iteration has converged
tol = 1e-8; 
% Define random symmetric matrix
A = randn(m,m);
A = A'*A;
% random normalized initial vector
v = randn(m,1);
v = v/norm(v);
V(:,1) = v;
% associated eigenvalue (Rayleigh quotient)
lambda(1) = v'*A*v;
% Find closest eigenvalue to lambda(1)
d = eig(A);
d = sort(d - lambda(1).*ones(m,1));
pos = find(d > 0);
if abs(d(pos(1)-1)) > d(pos(1))
    Lambda = d(pos(1)) + lambda(1);
else
    Lambda = d(pos(1)-1) + lambda(1);
end
% Identity matrix of size m
I = eye(m);
% Shifted inverse iteration
disp('      Shifted Inverse Iteration')
k = 2;
while (norm(A*V(:,k-1) - lambda(k-1)*V(:,k-1), inf) > tol)  
    w = (A-lambda(1)*I) \ V(:,k-1);
    V(:,k) = w/norm(w);
    lambda(k) = V(:,k)'*A*V(:,k);
    disp(sprintf('lambda(%d) = %10.12f', k-1, lambda(k)))
    k = k+1;
end
% Rayleigh quotient iteration
disp('      Rayleigh Quotient Iteration')
k = 2;
maxit = 30; 
iter = zeros(maxit, 1); 
diff = zeros(maxit, 1); 
%while (norm(A*V(:,k-1) - lambda(k-1)*V(:,k-1), inf) > tol)  
for i=1:maxit
    w = (A-lambda(k-1)*I) \ V(:,k-1);
    V(:,k) = w/norm(w);
    lambda(k) = V(:,k)'*A*V(:,k);
    disp(sprintf('lambda(%d) = %10.12f', k-1, lambda(k)))
    diff(i) = norm(A*V(:,k-1) - lambda(k-1)*V(:,k-1), inf)
    iter(i) = k-1; 
    k = k+1;
    
end

semilogy(iter, diff, 'o-') ; 
xlabel('Iterations'); 
ylabel('Difference'); 
disp(sprintf('Eigenvalue closest to lambda0 = %10.12f', Lambda))