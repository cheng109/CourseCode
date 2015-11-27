%% Problem #2
n = 30; 
k = n;

v = zeros(n, k+1); 
v(:,2) = ones(n,1)*1/sqrt(n);
v(:,2) = rand(n,1); 
beta = zeros(k,1); 
w = zeros(k, k); 
alpha = zeros(k, 1);  
% Lanczs method; 
e1 = zeros(n, 1); 
e1(1) = 1; 


n = 30; 
lambda1 = 0.1; 
lambdan = 100; 
rho = 0.9; 
A = eye(n); 
for i=1:30
    A(i) = lambda1+(i-1)/(n-1)*(lambdan-lambda1)*power(rho,(n-i)) 
end

val1 = zeros(30,1); 
val2 = zeros(30,1); 
val3 = zeros(30,1); 
val4 = zeros(60,1); 
iter = zeros(30,1); 
T = zeros(n+1, n);
v = zeros(n, n+1);

res = zeros(n);
beta = zeros(n+1,1); 
beta(1) = norm(b); 
v0 = zeros(n, 1);
v1 = rand(n, 1); 
v1 = ones(n,1)*1/sqrt(n);

v(1:n, 1) = v1;
alpha = zeros(n, 1);   
for j = 1 : 60
    wj = A*v1;
    alpha(j)  = v1'*wj;
    T(j, j) = alpha(j); 
    wj = wj - beta(j)*v0 -alpha(j) *v1;
    beta(j+1) = norm(wj);
    v0 = v1;
    v1 = wj/beta(j+1);
    if j ~= n
        T(j, j+1) = beta(j+1);
        T(j+1, j) = beta(j+1);
        v(1:n, j+1) = v1;
    end
  
    e1 = zeros(j, 1); 
    e1(1) = 1; 
    z = T(1:j, 1:j)\(norm(b)*e1); 
    x = v(1:n, 1:j)*z;
    res(j) =norm(beta(j+1)*z)-norm(b);
    
    iter(j) = j;
    I = eye(j); 
    val1(j) = log(norm(transpose(v(:,1:j))*v(:,1:j)-I)+1.0e-20) ;
    val2(j) = log(norm(transpose(v(:,1))*v(:,j))+1.0e-20);
    val4(j) = log(norm(A*v(:,j)-v(:,j+1)*T(j+1, j))+1.0e-20);
    
    if (j>3)
        val3(j) = log(norm(transpose(v(:,j-2))*v(:,j))+1.0e-20) 
    end
    if res(j) < tol
        break
    end
end



plot(iter(1:60), val4(1:60), '-o'); 
xlabel('k')
ylabel('val')

w(:,k) = A*v(:,k+1) ; 
alpha(k) = dot(w(:,k),v(:,k+1)); 


beta(3,1) 





%tol = 10e-6; 
%z = Tk\(norm(b)*e1)

