rank = load('comparisons_5.csv') ; 
id = csvread('items_5.csv'); 
%id = id(:,1)
rank = rank(:,3:8); 
[m, n] = size(rank); 
