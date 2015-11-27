function h= plotDisk(A); 
[n,m] = size(A); 
R =zeros(n, 1); 
lam = eig(A); 
for i=1:n 
    for j=1:n
        if i~=j
            R(i)=R(i)+abs(A(i,j)); 
        end
    end
    %diskPlot(A(i,i), 0, R(i)); 
    th = 0:pi/50:2*pi;
    xunit = R(i) * cos(th) + A(i,i);
    yunit = R(i) * sin(th) + 0;
    h = plot(xunit, yunit);
    scatter(lam(i), 0, 100); 
    axis equal; 
    hold on; 
end
end
