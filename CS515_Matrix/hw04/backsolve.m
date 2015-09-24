function x = backsolve(A, b) 
    % Assume matrix A is n by n upper triangular matrix; 
    % Vector b is n by 1. 
    n = length(b) ;         %% Get the length of the vector b
    x = zeros(n,1);         %% initiate solution Xl 
    x(n) = b(n)/A(n,n);     %% For the base case, x(n) = b(n)/A(n,n); 
    for i=n-1:-1:1
        temp = 0;           
        for j = i:n 
            temp = temp + A(i, j)*x(j);    %% Accumulate all the other terms
        end 
        x(i) = (b(i)-temp)/A(i,i);    %%  solve X(i)
    end 
end





