#include <iostream> 
#include <fstream> 
#include <cmath> 
using namespace std; 

int main() {
	ofstream f("Plot.txt"); 
	/*
	double x0 = -3; 
	double x1 = 0; 
	double x2 = M_E; 
	double x3 = M_PI; 
	
	// Problem # 1

	for(double x=-3; x<M_PI; x+=0.1) {
		double L30 = (x-x1)*(x-x2)*(x-x3)/((x0-x1)*(x0-x2)*(x0-x3)); 
		double L31 = (x-x0)*(x-x2)*(x-x3)/((x1-x0)*(x1-x2)*(x1-x3)); 
		double L32 = (x-x0)*(x-x1)*(x-x3)/((x2-x0)*(x2-x1)*(x2-x3)); 
		double L33 = (x-x0)*(x-x1)*(x-x2)/((x3-x0)*(x3-x1)*(x3-x2)); 

		//f << x << "\t" << L30 << "\t" << L31 << "\t" << L32 << "\t" << L33 << endl;  

	}

	// Proble #2 
	double lagrangeF; 
	double originF; 
	double diff; 
	for(double x=1; x<3; x+=0.01) {
		lagrangeF = -log(2)*(x-1)*(x-3) + 0.5*log(3)*(x-1)*(x-2); 
		originF = log(x) ; 
		diff = lagrangeF -originF; 
		//f <<  x << "\t" << lagrangeF << "\t" << originF << "\t" << diff << endl; 
	}

	
	// Problem #7 
	double Nx; 
	double b0 = 488.55; 
	double b1 = -0.2047; 
	double b2 = -2.5e-6; 
	double b3 = 0.092e-6; 
	double b4 = 1.344e-9; 

	double x0 = 10; 
	double x1 = 25; 
	double x2 = 50; 
	double x3 = 75; 
	double x4 = 100; 

	for(double x=5; x<101; x+=5) {
		Nx = b0 + b1*(x-x0) + b2*(x-x0)*(x-x1) + b3*(x-x0)*(x-x1)*(x-x2) + b4*(x-x0)*(x-x1)*(x-x2)*(x-x4); 
		f << x << "\t" << Nx << endl; 
	}	
	*/

	// Problem # 8 
	double Nx; 
	double b0 = 9.4; 
	double b1 = 0.09; 
	double b2 = -6e-5; 
	double b3 = 8.33e-8; 
	double b4 = -2.08e-10; 
	double b5 = 6.66e-13; 

	double x0 = 100; 
	double x1 = 200; 
	double x2 = 300; 
	double x3 = 400; 
	double x4 = 500; 
	double x5 = 600; 

	//for(double x=5; x<101; x+=5) {
	double x = 485; 
			Nx = b0 + b1*(x-x0) + b2*(x-x0)*(x-x1) + b3*(x-x0)*(x-x1)*(x-x2) 
		+ b4*(x-x0)*(x-x1)*(x-x2)*(x-x4)
		+ b5*(x-x0)*(x-x1)*(x-x2)*(x-x4)*(x-x5); 
	cout << Nx << endl; 

		//f << x << "\t" << Nx << endl; 
	//}	


	f.close(); 
	return 0; 	
}