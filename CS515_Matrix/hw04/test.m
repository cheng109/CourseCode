clear; 
clc; 
n = [10, 100, 500, 1000] ; 
trials = length(n);  
time = zeros(trials,1); 
error  = zeros(trials,1); 
repeat = 1; 
for t = 1: trials
    tic; 
    errorSum = 0 ; 
    for i=1:1
        A = rand(n(t),n(t)) ; 
        b = randn(n(t),1) ; 
   
        mine = linearSolver(A,b) ;
        matlab = A\b ;
        
        errorSum = errorSum + norm(mine-matlab)  ; 
    
    end 
    error(t) = norm(mine-matlab); 
    time(t) = toc ; 
end 
figure()
plot(n, time, '*-') 
plot(n, error, 'o-') 
