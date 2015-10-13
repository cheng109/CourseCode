#include <iostream> 
#include <vector> 
#include <cmath>
#include <iomanip>
using namespace std; 


void printMatrix(vector<vector<double> > A, int dim) {
	for(int i=0; i<dim; ++i) {
		for(int j=0; j<dim; ++j) {
			cout<< A[i][j] << " & " ; 
		}
		cout << " \\\\  "<< endl; 
	}
}

vector<double> multiply(vector<vector<double> > A, vector<double> x) {
	vector<double> b; 
	int dim = x.size(); 
	for(int i=0; i<dim; ++i) {
		double sum=0; 
		for(int j=0; j<dim; ++j) {
			sum+=A[i][j]*x[j]; 
		}
		b.push_back(sum); 
		//cout << sum << endl; 
	}
	return b; 
}

double getEigenValue(vector<vector<double> > A, vector<double> x) {
	int dim = x.size(); 
	double sum1 = 0; 
	double sum2 = 0; 
	vector<double> t = multiply(A, x); 
	for(int i=0; i<dim; ++i) {
		sum1 += x[i]*x[i]; 
		sum2 += t[i]*x[i]; 
	}
	return  sum2/sum1; 

}

vector<double> normVector(vector<double> A) {
	double sum =0; 
	for(int i=0; i<A.size(); ++i) {
		sum += A[i]*A[i]; 
	}
	sum = sqrt(sum); 
	for(int i=0; i<A.size(); ++i) {
		A[i] = A[i]/sum; 
		 
	}
	return A; 

}

double resNorm(vector<double> x1, vector<double> x2) {
	double res=0; 
	for(int i=0; i<x1.size(); ++i) {
		res+= (x2[i]-x1[i])*(x2[i]-x1[i]); 
	}
	return sqrt(res); 
}

void printVec(vector<double> v) {
	cout << "[" ; 
	for(int i=0; i<v.size()-1; ++i) {
		cout << setprecision(4) << v[i] << "," ; 
	}

	cout << v[v.size()-1] << "]"; 
}


vector<double> PowMethod(vector<vector<double> > A, vector<double> x0, double* lambda) {
	double tol=10e-6;
	vector<double> cur; 
	vector<double> pre = normVector(x0); 
	double res = 10; 
	int counter = 0; 

	while(counter <21) { 
		
		cur = normVector(multiply(A, pre)); 
		double temp= *lambda; 
		*lambda = getEigenValue(A, cur); 
		res = abs(*lambda-temp); 
		cout << setprecision(15)<< counter  << "\t" ; 
		printVec(cur); 
		cout << setprecision(15) << "\t Eigenvalue: " << *lambda << endl; 
		counter +=1;
		pre = cur; 
	}
	// Get the eigen value: 

	//*lambda = (innerProd(multiply(A, cur), cur)/innerProd(cur,cur)); 


	return cur;


}


int main() {

	//double data[] = {4, 0, 0, 0, 4, 0, 1, -1, 2}; 
	/*double data[] = {25, -5, 15, -5, 
						-5, 25, -15, 5, 
						-5, 5, 5, 5, 
						 5, -5, 15, 15}; */

	/*double data[] = { 0, 0, 0, 0.5, 
						1, 0, 0, 0.5, 
						0, 1, 0, -1.5, 
						0, 0, 1, 2.5 };  */

	double data[] = {1, 1, 1, 0, 
					0, 1, 1, 0 , 
					0, 0, 1, 0, 
					0, 0, 0, 0.5}; 

	vector<double> t;
	t.push_back(6); 
	t.push_back(9); 
	t.push_back(1); 
	t.push_back(4); 




	vector<vector<double> > A; 
	int dim = 4; 
	for (int i=0; i<dim; ++i) {
		vector<double>  temp; 
		for (int j=0; j<dim; ++j) {
			temp.push_back(data[i*dim+j]); 
		}	
		A.push_back(temp); 
	}


	printMatrix(A, dim); 
//	multiply(A, t); 
	double lambda; 
	PowMethod(A, t, &lambda); 
	cout << "EigenValue: " << lambda << endl; 
	return 0; 
}