#include <iostream> 
#include <cmath> 

using namespace std; 

double func(double t, double y, double y_0) {
	return 1*y ; 
}




double RK(double y0, double h, int iter_Num)) {
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
	double h = 0.01; 
	vector<double> y1; 
	vector<double> y2; 
	y1.pushback(100); 
	y2.pushback(10); 
	for(int i=0; i<2000; ++i) {
		//double val = RK(1, h, i); 
		double =RK(1, h, i);  
		//cout << "Iteration: " << i*h << "\t" << val << endl; 
		cout << i*h << "\t" << val << endl; 	
	}
	return 0; 
}