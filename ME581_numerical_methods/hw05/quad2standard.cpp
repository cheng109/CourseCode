#include <iostream>
#include <cmath> 
using namespace std; 

double func4(double u, double v ) {
	//return -3*(u+4)*(u+4)+27*(v+1)*(v+1); 
	//return 3*exp(-(u+1)*(u+1)-9*(v+1)*(v+1)); 

	double q1 = (1-u)*(1-v)*0.25; 
	double q2 = (1+u)*(1-v)*0.25; 
	double q3 = (1+u)*(1+v)*0.25; 
	double q4 = (1-u)*(1+v)*0.25; 
	//double x = 

	return 0; 
}

double func(double x, double y) {
	//return exp(-x*x-y*y); 
	//return -(x+3)*(x+3)+y*y; 
	//return x*y; 
	return exp(-(x+3)*(x+3)-y*y); 
}

int main() {
	double a = 1.0/sqrt(3); 

	double val = func4(a, a) + func4(a, -a) + func4(-a, a) + func4(-a, -a); 
	cout << func4(a, a) << endl; 
	cout << func4(a, -a) << endl; 
	cout << func4(-a, a) << endl; 
	cout << func4(-a, -a) << endl; 

	cout << "result: " << val << endl; 
	double xlim = 6; 
	double ylim = 4; 

	int n= 1000;
	int n1= xlim*n; 
	int n2= ylim*n;  
	double area = xlim*ylim/(n1*n2); 
	double result = 0; 
	for(int i=0; i<n1; ++i) {
		for (int j=0; j<n2; ++j) {
			double x = -3 + xlim*i/n1; 
			double y = -2 + ylim*j/n2; 
			//cout << func(x,y) << endl; 

			if(x<-1 && y>2*x+4) 
				continue; 
			if(x>1 && y<2*x-4)
				continue; 
			result += area*func(x, y); 
		}
	}

	cout << "True answer: " << result << endl; 
	return 0; 
}


