#include <iostream> 

using namespace std; 

int main() {

	double upper = 0.55; 
	double lower = -0.11; 
	int k=0; 



	double rho = 0.618; 
	double interval = upper - lower; 

	vector<double> a = lower + rho*interval; 
	vector<double> b = upper - rho*interval; 

	while (interval >0.1) {
	



	}




}