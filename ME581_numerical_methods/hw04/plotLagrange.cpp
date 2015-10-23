#include <iostream> 
#include <fstream> 
#include <cmath> 
using namespace std; 

int main() {
	ofstream f("Plot.txt"); 

	double x0 = -3; 
	double x1 = 0; 
	double x2 = M_E; 
	double x3 = M_PI; 

	for(double x=-3; x<M_PI; x+=0.1) {
		double L30 = (x-x1)*(x-x2)*(x-x3)/((x0-x1)*(x0-x2)*(x0-x3)); 
		double L31 = (x-x0)*(x-x2)*(x-x3)/((x1-x0)*(x1-x2)*(x1-x3)); 
		double L32 = (x-x0)*(x-x1)*(x-x3)/((x2-x0)*(x2-x1)*(x2-x3)); 
		double L33 = (x-x0)*(x-x1)*(x-x2)/((x3-x0)*(x3-x1)*(x3-x2)); 

		f << x << "\t" << L30 << "\t" << L31 << "\t" << L32 << "\t" << L33 << endl;  

	}

	f.close(); 
	return 0; 	
}