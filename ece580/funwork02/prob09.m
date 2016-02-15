[X, Y] = meshgrid(-1:0.1:1, -1:0.1:1); 
Z = (X-Y).^4 + 12*X.*Y - Y + X + 5; 
mesh(X, Y, Z) ; 

contour(X, Y, Z, 20 ) ; 
xlabel('X1') ; 
ylabel('X2'); 
box on; 