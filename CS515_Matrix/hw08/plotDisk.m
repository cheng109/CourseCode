%% plot Gershgorin circle. 
n = 4; 
A =rand(n,n); 
x = rand(n, 1); 
R =zeros(n, 1); 
%A = x*A*x'; 
c = randi(10, n);

for i=1:n 
    for j=1:n
        if i~=j
            R(i)=R(i)+A(i,j); 
        end
    end
    scatter(A(i,i), 0, R(i), c, 'filled', 'MarkerEdgeColor', 'k')
end
% Plot the disk centered at A(i,i) with radius R(i); 

