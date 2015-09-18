%% problem 4 
urlwrite('http://www.cs.nyu.edu/~roweis/data/usps_all.mat','usps_all.mat');
load('usps_all.mat'); 
 

%for j=1:1100
    image(reshape(data(:, 1, 10), [16,16])); 
%end 

%#image(data[0])
