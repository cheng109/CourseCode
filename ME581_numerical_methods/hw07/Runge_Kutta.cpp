#include <iostream> 
#include <cmath> 

using namespace std; 

double func(double t, double y) {
	return pow(y, 1/3.) ; 
}


double RK(double y0, double h, int iter_Num) {
	double a, b, c, d; 
	double y = y0; 
	double t = 0; 
	for(int i=0; i<iter_Num; ++i) {
		a = func(t, y); 
		b = func(t+0.5*h, y+0.5*h*a); 
		c = func(t+0.5*h, y+0.5*h*b); 
		d = func(t+h, y+h*c); 
		y = y + h/6*(a+2*b+2*c+d); 
		t = t + h; 
	}
	return y; 
}

int main() {
	double h = 0.02; 
	for(int i=0; i<50; ++i) {
		double val = RK(1.0e-16, h, i); 
		//cout << "Iteration: " << i*h << "\t" << val << endl; 
		cout << i*h << "\t" << val << endl; 	
	}



	return 0; 
}