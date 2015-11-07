maxit =1000; 
for i=1:maxit
    x = A*x; 
    x=x/norm(x); 
    lam = x'*A*x; 
end

