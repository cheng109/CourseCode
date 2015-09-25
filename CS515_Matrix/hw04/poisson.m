n = 10;
A = zeros((n+1)^2,(n+1)^2);
newA = zeros((n+1)^2-2, (n+1)^2-2); 
f = zeros((n+1)^2,1);
G = reshape(1:((n+1)^2), n+1, n+1)'; 
for i=0:n
 for j=0:n
     row = G(i+1,j+1);
     if i==0 || j == 0 || i==n || j==n
         % we are on a boundary
         f(row) = 0;
         A(row, row) = 1;     % For boundary points, we set the diagonal term to be 1. 
        
     else
         % we are NOT on a boundary
         f(row) = 1/n^2;
            A(row, G(i,j+1  )) = 1;             % Put the coefficients to the corresponding entry of matrix A. 
            A(row, G(i+1,  j)) = 1; 
            A(row, G(i+1,  j+1  )) = -4; 
            A(row, G(i+2,j+1  )) = 1 ; 
            A(row, G(i+1,  j+2)) = 1; 
        % end
            
     end
 end
end
u = A\f;
B = G 
for i=1:n+1
    for j =1:n+1
        B(i,j) = u(G(i,j))
    end
end

[X, Y] = meshgrid(1:n+1)
mesh(B)