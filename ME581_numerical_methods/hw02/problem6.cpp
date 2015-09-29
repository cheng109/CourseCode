#include <iostream>
#include <cmath> 

#define COL 13
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
    cout << x[i] <<  " \\\\ " ; 
  }
  cout << endl; 
}



int main() {
  double A[12][13] = {{0.894 , 0 , 0.707 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1,0 },
{0.447 , 0 , 0.707 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 0,0  } ,
{-0.894 , -0.949 , 0 , 0 , 0 , 0 , 0 , 0.949 , 0.894 , 0 , 0 , 0,0 },  
{-0.447 , 0.316 , 0 , 0 , 1 , 0 , 0 , 0.316 , -0.316 , 0 , 0 , 0,0 },  
{0 , 0.949 , -0.707 , 0.949 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,0  },
{0 , -0.316 , -0.707 , 0.316 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,0 }, 
{0 , 0 , 0 , -0.949 , 0 , 0.949 , 0 , 0 , 0 , 0 , 0 , 0 ,0  },
{0 , 0 , 0 , -0.316 , -1 , -0.316 , 0 , 0 , 0 , 0 , 0 , 0 ,0  },
{0 , 0 , 0 , 0 , 0 , -0.949 , 0.707 , -0.949 , 0 , 0 , 0 , 0 ,0 }, 
{0 , 0 , 0 , 0 , 0 , 0.316 , -0.707 , -0.316 , 0 , 0 , 0 , 0 ,0  },
{0 , 0 , 0 , 0 , 0 , 0 , -0.707 , 0 , 0.894 , 0 , 0 , 0 ,0 },
{0 , 0 , 0 , 0 , 0 , 0 , 0.707 , 0 , 0.447 , 1 , 0 , 0 ,0 }}; 
  int row = 12; 
  int col = 13; 

  //double b[12] = {0 , 0 , 0 , 0 , 0 , 500 ,  0 , 1000 , 0 , 500 , 0 , 0}; 
  //double b[12] = {0 , 0 , 0 , 0 , 0 , 500 ,  0 , 1000 , 0 , 1500 , 0 , 0}; 
  //double b[12] = {0 , 0 , 0 , 0 , 0 , 1500 ,  0 , 1000 , 0 , 500 , 0 , 0}; 
    double b[12] = {0 , 0 , 0 , 0 , -1000 , 0 ,  -500 , 0 , 0 , 0 , 0 , 0}; 
  //double b[12] = {0 , 0 , 0 , 0 , 0 , 0 ,  500 , 0 , 1000 , 0 , 0 , 0}; 
  // Replace the last column 
  for(int i=0; i<12; ++i) {
    A[i][12] = b[i]; 
  }

  
  partialPivot(A, row, col); 
  cout << "After scale partial pivoting : " << endl ;
  printMatrix(A, row, col); 
  

  double* x2 = backsolve(A, row, col); 
  cout << "The scaled pivoting result X:   " << endl; 
  printVector(x2, row) ; 
  
  delete[] x2; 

  return 0;
}


