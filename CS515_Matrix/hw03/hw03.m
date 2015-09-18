%% problem 1 
A= [5, -5; 2, -2] 
[u,s,v] = svd(A) 
B = [5, -5; 2, -2; 0, 0 ]
[u1,s2,v3] = svd(A)


u = [0.93, -0.37, 0; 0.37, 0.93, 0; 0, 0, 0] 
s = [7.6, 0 ;0, 0; 0, 0] 
v = [0.707, -0.707; 0.707, 0.707] 
B = u*s*v
%% Test 


%% problem 4 
urlwrite('http://www.cs.nyu.edu/~roweis/data/usps_all.mat','usps_all.mat');
load('usps_all.mat'); 
%image(reshape(data(:, 1, 10), [16,16])); 
 
residual =double(data) - repmat(mean(data),256, 1,1); 
% Reshape the matrix
m1 = reshape(residual, [256,11000])
[u,s, ~] = svd(m1) 
%image(reshape(u(:, 1), [16,16]))
%image(reshape(m1(:,10005), [16,16]))
mm = zeros(1,10); 
leadingV = zeros(256,10); 

for i=1:10
    [u,s,~] = svd(residual(:,:,i)); 
    mm(i)=s(1,1); 
    leadingV(:,i)=u(:,1); 
end
imagesc(reshape(leadingV(:, 2), [16,16]))


