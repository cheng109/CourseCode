n = 100; 
 
tol = 1.0e-8; 
on = ones(n,1);
A = spdiags([-2*on 4*on -2*on],-1:1,n,n);
b = ones(n,1);

[res_1, x_1] = CGL(A, b, n,  tol, 200 ); 
%[x, res] = CG_lanczos(A, b, n, tol, 100); 

[x_2, res_2] = cg(A, b, 200, tol)

d1 = norm(A*x_1-b) 
d2 = norm(A*x_2-b)

lim = 50; 

x_iter = zeros(lim,1); 
for i=1:lim
    x_iter(i) = i; 
end


count = 0; 
for t = 1:size(res_2)
    count = count + 1; 
    if res_2(t)<1.0e-8
        break; 
    end
end
count
size(res_2)
%plot(x_iter, res_1(1:lim), '*')
%xlabel('Iteration')
%ylabel('Residual from CGL.m') 

