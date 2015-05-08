#include <iostream>
#include <vector>
#include <random>
#include <chrono>

using namespace std; 

typedef vector<vector<double> > matrix; 

matrix iniMatrix(int d) {
  matrix m; 
  for(int i=0; i<d; ++i) {
    vector<double> temp(d, 0);
    m.push_back(temp); 
  }
  return m; 
}


matrix Cholesky(matrix cov, int d) {
  matrix A = iniMatrix(d); 
  for(int i=0; i<d; ++i) {
    double temp1=0; 
    for(int j=0; j<=i; ++j) {
      
      if (j<i){
	double sum = 0; 
	for(int k=0; k<=j-1; ++k)
	  sum+=A[i][k]*A[j][k];
	A[i][j]=(cov[i][j]-sum)/A[j][j]; 
	temp1 += A[i][j]*A[i][j]; 	
      }
      if(i==j) {

	A[i][i]= sqrt(cov[i][j]-temp1); 
      }
    }
  }
  return A; 
}

void printMatrix(matrix m, int d) {
  for(int i=0; i<d; ++i) {
    for(int j=0; j<d; ++j) {
      cout << m[i][j] << "\t" ; 
    }
    cout << endl; 
  }

}

int main() {
  int d = 6;
  matrix cov = iniMatrix(d);

  double sigma = 0.15;
  double rho = 0.3;

  
  for (int i=0; i<d; ++i) {
    for (int j=0; j<d; ++j) {
      if(i==j) cov[i][j]=sigma*sigma; 
      if(i!=j) cov[i][j]=rho*sigma*sigma; 
    }
  }
  printMatrix(cov, d); 
  
  matrix A = Cholesky(cov, d);
  printMatrix(A, d); 


  

  return 0;

}

