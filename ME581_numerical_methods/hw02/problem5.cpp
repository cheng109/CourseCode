#include <iostream>
#include <cmath> 

#define COL 6
using namespace std; 

void printMatrix(double A[][COL], int row, int col) ; 

void partialPivot(double A[][COL], int row, int col) {
  for(int i=0; i<row; ++i) {
    // Find which row is the largest; 
    double max = abs(A[i][i]); 
    int maxIndex=i; 
    for(int iter=i+1; iter<row; ++iter) {
      if (abs(A[iter][i])>max){
	max = abs(A[iter][i]); 
	maxIndex=iter; 
      }
    }
    //Switch two rows;
    if(maxIndex!=i) {
      for(int iter=i; iter<col; ++iter) {
	double temp = A[i][iter]; 
	A[i][iter] = A[maxIndex][iter]; 
	A[maxIndex][iter] = temp;
      }
    }
    // Start elimination; 
    for (int iter=i+1; iter<row; ++iter) {
      double factor = -A[iter][i]/A[i][i]; 
      for (int j= i; j<col; ++j) {
	A[iter][j] += factor*A[i][j]; 
      }
    }
  }
}

double getMax(double v[], int length) {
  double max = abs(v[0]); 
  for(int i=0; i<length; ++i) {
    if (abs(v[i])>max) 
      max = abs(v[i])  ; 
  }
  return max; 
}


void scalePivot(double A[][COL], int row, int col) {
  for(int i=0; i<row; ++i) {
    // Get the maximum of the row;
    double rowMax = getMax(A[i], COL); 

    double max = abs(A[i][i]/rowMax);
    int maxIndex=i;
    for(int iter=i+1; iter<row; ++iter) {
      double rowMax = getMax(A[iter], COL); 
      if (abs(A[iter][i]/rowMax)>max){
        max = abs(A[iter][i]/rowMax);
        maxIndex=iter;
      }
    }
    //Switch two rows;                                                                                                                                            
    if(maxIndex!=i) {
      for(int iter=i; iter<col; ++iter) {
        double temp = A[i][iter];
        A[i][iter] = A[maxIndex][iter];
        A[maxIndex][iter] = temp;
      }
    }
    // Start elimination;                                                                                                                                         
    for (int iter=i+1; iter<row; ++iter) {
      double factor = -A[iter][i]/A[i][i];
      for (int j= i; j<col; ++j) {
        A[iter][j] += factor*A[i][j];
      }
    }
  }
}


double* backsolve(double A[][COL],int row, int col) {
  double* x = new double(row); 
  x[row-1] = A[row-1][row]/A[row-1][row-1];  
  for(int i=row-2; i>=0; --i) {
    double sum=0; 
    for(int iter=i+1; iter<col-1; ++iter) {
      sum += A[i][iter]*x[iter]; 

    }
    x[i] =  (A[i][col-1] - sum)/A[i][i]; 

  }
  return x; 
}


void printMatrix(double A[][COL], int row, int col) {
  for(int i=0; i<row; ++i) {
    for(int j=0; j<col; ++j) {
      cout << A[i][j] << "\t\t" ; 
    }
    cout << endl; 
  }
  cout << endl; 
}

void printVector(double* x, int length) {
  for (int i=0; i<length; ++i) {
    cout << x[i] << endl ; 
  }
  
}



int main() {
  double B[5][6] = {{-9 , 11 , -21,      63 , -252 ,-356},
		    {70 , -69 , 141 , - 421 , 1684,2385},  
		    {-575 , 575 , -1149 , 3451 , -13801, -19551}, 
		    {3891 , -3891 , 7782 , -23345 , 93365, 132274}, 
		    {1024 , -1024 , 2048 , -6144 , 24572, 34812}}; 
  int row = 5; 
  int col = 6; 

  
  scalePivot(B, row, col); 
  cout << "After scale partial pivoting : " << endl ;
  printMatrix(B, row, col); 
  

  double* x2 = backsolve(B, row, col); 
  cout << "The scaled pivoting result X:   " << endl; 
  printVector(x2, row) ; 
  
  delete[] x2; 

  return 0;
}


