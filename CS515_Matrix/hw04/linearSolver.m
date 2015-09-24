function x = linearSolver(A, b)     
    [L, U] = lu(A)
    x1 = forwardsolve(L, b); 
    x = backsolve(U, x1); 
end 