function [U, iter] = jacobian(A, b)
[N,t] = size(b); 
U = zeros(N,1) ; 
%diff = zeros(20, 1) ; 
true = A\b; 
diff = 100; 
iter = 0 ; 
while diff > 1.0e-4 
    temp = U; 
    for i=1:N
        sum = 0; 
        for j=1:N
            if i~=j
                sum = sum + A(i,j)*temp(j); 
            end
        end
        U(i) = 1/A(i,i)*(b(i)-sum); 
    end
    diff  =  norm(U- true)  
    iter = iter + 1 ; 
end 

end