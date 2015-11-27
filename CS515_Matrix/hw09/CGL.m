function [res, x] = CGL(A, b, n, tol, num)
T = zeros(n, n);
v = zeros(n, n+1);
res = zeros(n);
alpha = zeros(n, 1); 
beta = zeros(n+1,1); 
beta(1) = norm(b); 
v0 = zeros(n, 1);
v_temp = b/beta(1);
v(1:n, 1) = v_temp;
  
for j = 1 : num
    wj = A*v_temp;
    alpha(j)  = transpose(v_temp)*wj;
    T(j, j) = alpha(j); 
    wj = wj - beta(j)*v0 -alpha(j) *v_temp;
    beta(j+1) = norm(wj);
    v0 = v_temp;
    v_temp = wj/beta(j+1);
    if j ~= n
        T(j, j+1) = beta(j+1);
        T(j+1, j) = beta(j+1);
        v(1:n, j+1) = v_temp;
    end
  
    e1 = zeros(j, 1); 
    e1(1) = 1; 
    z = T(1:j, 1:j)\(norm(b)*e1); 
    x = v(1:n, 1:j)*z;
    res(j) =norm(beta(j+1)*z)-norm(b);
    if res(j) < tol
        break
    end
end

return