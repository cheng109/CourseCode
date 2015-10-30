function [U, iter] = jacobian(A, b)

% Assume A is a sparse matrix
[N,t] = size(b); 
U = zeros(N,1) ;
%diff = zeros(20, 1) ; 
[J,I,V] = find(A); 
res = 100; 
iter = 0 ; 
nb = norm(b); 
[len,t]= size(I);  

while res > 1.0e-4 
   
    temp = U; 
    ss = 4*temp; 
    for index=1:len
        i = I(index); 
        j = J(index); 
        ss(i) = ss(i) + A(i,j)* temp(j); 
    end
    for i=1:N
        U(i) = 1.0/A(i,i)*(b(i)-ss(i)); 
    end
    res  =  norm(b-A*U)/nb      
    iter = iter + 1; 

end

end