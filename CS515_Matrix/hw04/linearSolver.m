function x = linearSolver(A, b)     
    [L, U, P] = lu(A);
    x1 = forwardsolve(L, P*b); 
    x = backsolve(U, x1); 
end 