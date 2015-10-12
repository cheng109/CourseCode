#include <iostream> 
#include <vector> 
#include <cmath>
using namespace std; 

double resNorm(vector<double> x1, vector<double> x2); 
vector<double> GaussSeidel(vector<vector <double> > A, vector<double> b, vector<double> x0) {
	int n = b.size(); 
	vector<double> pre(n, 0); 
	vector<double> cur(n, 0); 
	double tol = 10e-6; 
	double res =10; 
	while(res>tol) {
		for(int i=0; i<n; ++i) {
			double sum = 0; 
			for(int j=0; j<n; ++j) {
				if(j<i) 
					sum+=A[i][j]*cur[j]; 
				if(j>i) 
					sum+=A[i][j]*pre[j]; 
			}	
			cur[i] = (b[i]-sum)/A[i][i]; 

		}	
		res =  resNorm(cur, pre); 
		pre = cur; 
		cout << "residual: " << res << endl;  
	}
	return cur; 
}

double resNorm(vector<double> x1, vector<double> x2) {
	double res=0; 
	for(int i=0; i<x1.size(); ++i) {
		res+= (x2[i]-x1[i])*(x2[i]-x1[i]); 
	}
	return sqrt(res); 
}


int main(){
	//double A[6][6]; 
	vector<vector<double> > A; 
	double data[] = {5, -1, 0, -1, 0, 0, 
					-1, 5, -1, 0, -1, 0, 
					0, -1, 5, 0, 0, -1, 
					-1, 0, 0, 5, -1, 0, 
					0, -1, 0, -1, 5, -1, 
					0, 0, -1, 0, -1, 5,
					}; 
	int dim=6; 
	for(int i=0; i<dim; ++i) {
		vector<double> temp; 
		for (int j=0; j<dim; ++j) {
			temp.push_back(data[dim*i+j]); 
		}
		A.push_back(temp); 
	}


	// Print A
	for(int i=0; i<dim; ++i) {
		for(int j=0; j<dim; ++j) {
			cout<< A[i][j] << " & " ; 
		}
		cout << "\\\\ "<< endl; 
	}

	double tempB[] = {-5, 1, 1, -2, 1, 2}; 
	double tempX[] = {1, 2, 3, 4, 5, 6}; 

	vector<double> x0, b; 

	for(int i=0; i<dim; ++i) {
		b.push_back(tempB[i]); 
		x0.push_back(tempX[i]); 
	}
	
	
	cout << "hello" << endl; 	
	vector<double> result = GaussSeidel(A, b, x0); 
	cout << "Result: " << endl; 
	for (int i=0; i<dim; ++i) {
		cout << result[i] << endl; 
	}		
	//cout << resNorm(b, b) << endl;


	return 0; 
}

