function x = forwardsolve(A, b) 
    % Assume matrix A is n by n upper triangular matrix; 
    % Vector b is n by 1. 
    n = length(b) ;         %% Get the length of the vector b
    x = zeros(n,1);         %% Initiate solution Xl 
    x(1) = b(1)/A(1,1);     %% For the base case, x(1) = b(1)/A(1,1); 
    for i=2:n
        temp = 0; 
        for j = 1:i 
            temp = temp + A(i, j)*x(j); %% Accumulate all the other terms
        end 
        x(i) = (b(i)-temp)/A(i,i);  %%  solve X(i)
    end 
end
