#include <iostream> 
#include <cmath>
using namespace std; 



//  Initial condition at time t=0; 

class Grid {

	double dx; 
	double dt; 
	int nX; 
	int nT; 
	double c;  // coefficient;
	

public: 
	double ** u;
	Grid(double dx, double dt,  int nX, int nT, double c): dx(dx), dt(dt), nX(nX), nT(nT), c(c) {
		u = (double **) malloc(nT*sizeof(double*)); 
		for(int i=0; i<nT; ++i) 
			u[i] = (double *) malloc(nX*sizeof(double)); 
	}
	void setBondary(); 
	void eulerMethod(); 

}; 

void Grid::setBondary() {
	// Problem 1; 
	// u(t,x=0)=0   &  u(t,x=1)=0
	for(int i=0; i< nT; ++i) {
		u[i][0] = 0; 
		u[i][nX-1] = 0;  
	}
	for(int j=0; j<nX; ++j) {
		double x = j*dx; 
		u[0][j]= sin(M_PI*x); 
	}
}

void Grid::eulerMethod() {
	for(int i=0; i<nT-1; ++i) 
		for(int j=1; j<nX-1; ++j) 
			u[i+1][j]=u[i][j] + c*dt/(dx*dx)*(u[i][j+1]-2*u[i][j]+u[i][j-1]); 
}


double analyticalSolution(double t, double x) {

	return exp(-M_PI*M_PI*t)*sin(M_PI*x); 
}

int main() {
	double dx = 0.5; 
	double dt = 0.001; 
	double startX = 0; 
	double startT = 0; 
	double endX = 1; 
	double endT = 0.03; 
	int nX = 1./dx+1; //(int) (endX-startX)/dx+1; 
	int nT = 1./dt+1; //(int) (endT-startT)/dt+2;
	cout << nX << "\t"  << nT << endl; 
	double c = 1; 
	Grid grid(dx, dt, nX, nT, c); 
	grid.setBondary(); 
	grid.eulerMethod(); 
	// Analytical solution; 

	for(int i=10; i<11; ++i) {
		for (int j=0; j<nX; ++j ) {
			double diff = grid.u[i][j] - analyticalSolution(dt*i, dx*j); 
			cout << analyticalSolution(dt*i, dx*j) << "\t" << grid.u[i][j] << "\t"  << endl; // diff <<endl ;  
		}
	}

	return 0; 
}