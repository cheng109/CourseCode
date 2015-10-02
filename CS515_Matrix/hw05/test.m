% TEst 

n=10; 
Q = qr(randn(n)); 
D = abs(randn(n,1)); 
A = Q*diag(D)*Q'; 

L = cholesky(A) ; 
matlabL = chol(A, 'lower') ; 

d = norm(matlabL -L) 



%%
tic; 
L = cholesky(A)
myTime = toc
tic; 
matlabL = chol(A, 'lower')
MatlabTime = toc

%% part 4

repeat = 10; 
myT = zeros(1,20); 
matlabT = myT;
size = myT; 
for i=(1:20)
    n = (i+2)^2+1;
    size(i) = n;
    myT(i) = 0; 
    matlabT(i) = 0; 
    for t=(1:repeat)
        a = rand(n,n); 
        A = a'*a; 
        tic; 
        L = chol(A, 'lower'); 
        myT(i) = myT(i) + toc; 
        Y = lu(A) ;
        matlabT(i) = matlabT(i) + toc; 
    end
    
    
end
n = [1:20]  ;  
plot(size,myT, '*-', size, matlabT, 'o-')
legend('Cholesky Time', 'LU Time') ; 
xlabel('Matrix size'); 
ylabel('Time'); 


%%  Problem # 2 
q = 500; 
s = 7; 
z = zeta(s); 
h = z-sum((1:(q-1)).^(-s)) 







