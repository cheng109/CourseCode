#include <iostream>
#include <cmath> 
using namespace std; 

double func4(double u, double v) {
	//return -3*(u+4)*(u+4)+27*(v+1)*(v+1); 
	//return 3*exp(-(u+1)*(u+1)-9*(v+1)*(v+1)); 
	return 0.5*(1+3*u)*(3+u-v-3*u*v); 
}

double func(double x, double y) {
	return exp(-x*x-y*y); 
	//return -(x+3)*(x+3)+y*y; 
}

int main() {
	double a = 1.0/sqrt(3); 

	double val = func4(a, a) + func4(a, -a) + func4(-a, a) + func4(-a, -a); 
	cout << func4(a, a) << endl; 
	cout << func4(a, -a) << endl; 
	cout << func4(-a, a) << endl; 
	cout << func4(-a, -a) << endl; 

	cout << "result: " << val << endl; 



	int n= 1000;
	int n1= 2*n; 
	int n2= 6*n;  
	double area = 2.0*6.0/(n1*n2); 
	double result = 0; 
	for(int i=0; i<n1; ++i) {
		for (int j=0; j<n2; ++j) {
			double x = 0 + 2.0*i/n1; 
			double y = 0 + 6.0*j/n2; 
			//cout << func(x,y) << endl; 
			result += area*func(x, y); 
		}
	}

	cout << "True answer: " << result << endl; 
	return 0; 
}


