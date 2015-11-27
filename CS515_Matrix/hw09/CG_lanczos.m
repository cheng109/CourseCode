function [x, res] = CG_lanczos(A, b, n, tol, iter)

v = zeros(n, n+1); 
v(:,2) = b/norm(b);
beta = zeros(n+1,1); 
beta(:, 1) = norm(b); 
alpha = zeros(n, 1);  

w = zeros(n, n); 
T = zeros(n+1, n); 
res = 10000000; 
%while (res> tol)
for i=1:1
    for j = 1:iter
       
        wj = A*v(:,j+1);
        alpha(j) = dot(wj,v(:,j+1));
        T(j, j) = alpha(j); 
        w(:,j) = wj-alpha(j)*v(:,j+1)-beta(j)*v(:, j);
        beta(j+1) = norm(w(:, j));
        v(:,j+2) = w(:,j)/beta(j+1);
        if j~=n
       
        T(j, j+1) = beta(j); 
        T(j+1, j) = beta(j); 
        end 
   
    
    w(:,j) = A*v(:,j+1) ;
    alpha(j) = dot(w(:,j),v(:,j+1));
    beta(j+1) = norm(w(:,j));
    e1 = zeros(j, 1); 
    e1(1) = 1; 
    z = T(1:j, 1:j)\(norm(b)*e1); 
    x = v(1:n, 1:j)*z; 
    res= norm(T(1:j,1:j)*z-norm(b)*e1)
    end
end

