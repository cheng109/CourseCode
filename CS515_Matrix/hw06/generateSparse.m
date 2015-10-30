%% problem2 (a) 
num = [10, 50, 100, 500]; 
tt = zeros(1,4); 
%function A = generateSparse(N)
for t=1:3 
    N = num(t); 
    tic; 
A = sparse((N-1)*(N-1),(N-1)*(N-1));

for i=1:(N-1)*(N-1)
        A(i,i) = -4; 
       
        col = mod(i,N-1);
        if col==0
            col = N-1; 
        end
        row = ceil(i/(N-1)); 
        if row-1>=1
            A(i, (row-2)*(N-1) + col) = 1; % UP
        end
        if row+1 <=N-1
            A(i, (row)*(N-1) + col) = 1; % DOWN
        end
        if col-1>=1
            A(i, (row-1)*(N-1) + col-1) =1 ; % LEFT
        end
        if col+1<=N-1
            A(i, (row-1)*(N-1) + col+1) = 1; % RIGHT
        end
end
   tt(t) = toc;  
end
%A= full(A)

%tt = [ 0.0086 ,   0.0438  ,  0.3845 , 513.0644]
%%  %% problem2 (b) 
num = [10, 50, 100, 500]; 
tt = zeros(1,4); 
%function A = generateSparse(N)
for t=2:2 
    N = num(t); 
    tic; 


nz = (N-1)^2 + 4*(N-1)*(N-2);
I = zeros(nz,1);
J = zeros(nz,1);
V = zeros(nz,1);

index = 1; 

for i=1:(N-1)*(N-1)
         I(index) = i;
         J(index) = i; 
         V(index) = -4; 
         index = index+1; 
         
        col = mod(i,N-1); 
        if col==0
            col = N-1; 
        end
        row = ceil(i/(N-1)); 
        if row-1>=1
            % UP
            I(index) = i;
            J(index) = (row-2)*(N-1) + col; 
            V(index) = 1; 
            index = index+1; 
        end
        if row+1 <=N-1
             % DOWN
            I(index) = i;
            J(index) = (row)*(N-1) + col;  
            V(index) = 1;
             index = index+1; 
        end
        if col-1>=1
             % LEFT
            I(index) = i;
            J(index) = (row-1)*(N-1) + col-1;  
            V(index) = 1;
             index = index+1; 
        end
        if col+1<=N-1
            % RIGHT
            I(index) = i;
            J(index) = (row-1)*(N-1) + col+1;  
            V(index) = 1;
            index = index+1; 
        end
end

A = sparse(I,J,V,(N-1)*(N-1),(N-1)*(N-1));
tt(t) = toc ; 
b = ones((N-1)*(N-1), 1) ; 
[U, iter]  = jacobian(A, b); 

end 



%%
tt1 = [ 0.0086 ,   0.0438  ,  0.3845 , 513.0644]
%plot(num, tt, '-*'); 
plot(num, tt1, '-ro') ; 
xlabel('N');
ylabel('Time(seconds)'); 
