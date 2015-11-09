#include <iostream> 
#include <cmath>
using namespace std; 
struct Point{
	double x; 
	double y; 
	Point(double a, double b):x(a), y(b) {}

}; 

double func4(double u, double v, Point a1, Point a2, Point a3, Point a4, 
	double a, double b, double c ) {
	//return -3*(u+4)*(u+4)+27*(v+1)*(v+1); 
	//return 3*exp(-(u+1)*(u+1)-9*(v+1)*(v+1)); 

	double q1 = (1-u)*(1-v)*0.25; 
	double q2 = (1+u)*(1-v)*0.25; 
	double q3 = (1+u)*(1+v)*0.25; 
	double q4 = (1-u)*(1+v)*0.25; 
	double x = a1.x*q1 + a2.x*q2 + a3.x*q3 + a4.x*q4; 
	double y = a1.y*q1 + a2.y*q2 + a3.y*q3 + a4.y*q4; 
	double J = a+ b*u + c*v; 
	//double original = x*y; 
	double original = exp(-(x+3)*(x+3)-y*y); 
	return original*J; 
}

void jacobian(Point a1, Point a2, Point a3, Point a4, double *a, double *b, double *c) {
	*a = 0.125*((a4.x-a2.x)*(a1.y-a3.y)+(a3.x-a1.x)*(a4.y-a2.y));  // Const
	*b = 0.125*((a4.x-a3.x)*(a2.y-a1.y)+(a1.x-a2.x)*(a4.y-a3.y)); 	// Coeffience for u; 
	*c = 0.125*((a4.x-a1.x)*(a2.y-a3.y)+(a3.x-a2.x)*(a4.y-a1.y)); 	// Coeffience for v; 
	
	cout << "const:  "  << *a << endl; 
	cout << "uCoeff: "	<< *b << endl; 
	cout << "vCoeff: "  << *c << endl; 


}

int main() {
	/*
	Point a1(0, 0); 
	Point a2(2, 0); 
	Point a3(4, 4); 
	Point a4(0, 4);  */

	// Problem #7 
	
	Point a1(-3, -2); 
	Point a2(1, -2); 
	Point a3(3, 2); 
	Point a4(-1, 2); 	

	double a, b, c; 

	jacobian( a1,  a2,  a3,  a4, &a, &b, &c); 


	double coef = 1.0/sqrt(3); 

	double val = func4(coef, coef, a1, a2, a3, a4, a, b, c) 
				+ func4(coef, -coef, a1, a2, a3, a4, a, b, c) 
				+ func4(-coef, coef, a1, a2, a3, a4, a, b, c) 
				+ func4(-coef, -coef, a1, a2, a3, a4, a, b, c); 
	cout << func4(coef, coef, a1, a2, a3, a4, a, b, c) << endl; 
	cout << func4(coef, -coef, a1, a2, a3, a4, a, b, c) << endl; 
	cout << func4(-coef, coef, a1, a2, a3, a4, a, b, c) << endl; 
	cout << func4(-coef, -coef, a1, a2, a3, a4, a, b, c) << endl; 

	cout << "result: " << val << endl; 


	return 0 ; 
}