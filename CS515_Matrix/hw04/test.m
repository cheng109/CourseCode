clear; 
clc; 
n = [5, 100, 200,  500, 800, 1000,2000] ; 
trials = length(n);  
mytime = zeros(trials,1); 
matlabtime = zeros(trials,1); 
error  = zeros(trials,1); 
repeat = 10; 
for t = 1: trials
   
    errorSum = 0 ; 
    for i=1:repeat
        A = rand(n(t),n(t)) ; 
        b = randn(n(t),1) ; 
        tic; 
        mine = linearSolver(A,b) ;
        mytime(t) = mytime(t) + toc; 
        tic; 
        matlab = A\b ;
        matlabtime(t) = matlabtime(t) + toc; 
        errorSum = errorSum +  norm(mine-matlab)/norm(matlab)   ; 
    
    end 
    
    error(t) = errorSum/repeat; 
    
end 
figure()
plot(n, mytime, '*-', n, matlabtime, 'o-') 
xlabel('Size of matrix')
ylabel('Running time (s)')
legend('myLinearSolver', 'Matlab')
% plot(n, error, '*-') 
% xlabel('Size of matrix')
% ylabel('Error (s)')
