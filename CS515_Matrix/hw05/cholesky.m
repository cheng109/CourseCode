% We assume the matrix is postive definite. 
function L = cholesky(A)
n = size(A); 
n = n(1); 
L = zeros(n,n);
%L(1,1) = sqrt(A(1,1)); 
for i=(1:n)
    sum1 =0;     
    for j=(1:i) 

        if i==j
            L(j,j) = sqrt(A(j,j)-sum1); 
        else 
            sum2 = 0; 
            for k = (1:j-1) 
                sum2 = sum2 + L(i,k)*L(j,k); 
            end 
            
            L(i,j) = 1/L(j,j)*(A(i,j)-sum2); 
        end 
        sum1= sum1 + L(i,j)^2;   
    end 
end 
end 




