#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#define NUM 3000
#include <ctime>
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
      if(i==j) 
	A[i][i]= sqrt(cov[i][j]-temp1); 

    }
  }
  return A; 
}

void printMatrix(matrix m, int d) {
  for(int i=0; i<d; ++i) {
    for(int j=0; j<d; ++j)
      cout << m[i][j] << "\t" ; 
    cout << endl; 
  }

}

vector<double> correlatedGDB(int d, matrix A, vector<double> v) {
  // Generate d independent gaussian;
  // srand(time(NULL));
  //  unsigned seed = chrono::system_clock::now().time_since_epoch().count();
  //default_random_engine generator(seed);
  //  normal_distribution<double> distribution(0,1);
  /*vector<double> v; 
  for(int i=0; i<d; i++) {
    double Z = distribution(generator);
    v.push_back(Z);
  }
  */
  // Matrix Multply
  vector<double> corrZ(d, 0); 
  for(int i=0; i<d; ++i) {
    for(int j=0; j<d; ++j) {
      corrZ[i]+=A[i][j]*v[j];
    }
  }
  return corrZ; 
}

int main() {
  int d = 1;
  matrix cov = iniMatrix(d);

  double sigma = 0.15;
  double rho = 0.0;

  
  for (int i=0; i<d; ++i) {
    for (int j=0; j<d; ++j) {
      if(i==j) cov[i][j]= sigma*sigma; 
      if(i!=j) cov[i][j]= rho*sigma*sigma; 
    }
  }
  printMatrix(cov, d); 
  matrix A = Cholesky(cov, d);
  printMatrix(A, d); 

  unsigned seed = chrono::system_clock::now().time_since_epoch().count();
  default_random_engine generator(seed);
  normal_distribution<double> distribution(0,1);


  
  double T =1; 
  double K=100*d;
  int steps = 500;
  double dt = T/steps; 
  double r=0.04; 
  double S0 =100; 
  vector<double> payoff(NUM, 0); 
  double sum2=0; 
  for (int t= 0; t<NUM;++t) {
    double temp5 = 0; 
    vector<double> stock(d, S0);
    for (int step=0; step<steps; ++step) { 
      vector<double> v; 
      for(int i=0; i<d; i++) {
	double Z = distribution(generator);
	v.push_back(Z);
      }
      
      
      /*vector<double> v;
      
      // Matrix Multply
      vector<double> corrZ(d, 0);
      for(int i=0; i<d; ++i) {
	for(int j=0; j<d; ++j) {
	  corrZ[i]+=A[i][j]*v[j];
	}
	//cout << corrZ[i] << endl; 
      }
      */
      vector<double> corrZ =  correlatedGDB(d, A, v );
       
      for(int i=0; i<d; ++i)  {
	//	corrZ[i]=sigma*v[i]; 
	//stock[i]= stock[i] + stock[i]*r*dt+stock[i]*sqrt(dt)*corrZ[i] + 0.5*(corrZ[i]*corrZ[i]-sigma*sigma)*dt;
	stock[i]= stock[i] + stock[i]*r*dt+stock[i]*sqrt(dt)*corrZ[i] + 0.5*(corrZ[i]*corrZ[i]-sigma*sigma)*dt;
      }
    }
    // sum over the payoff at Time
    
    for(int mm=0;  mm<d; ++mm) {
      if (stock[mm]>100){
	//cout << stock[mm] << endl; 
	sum2+=stock[mm]-100;
      }
    }
    
    
  }
  cout << "Price is : " << sum2/NUM*exp(-r*T) << endl; 
  //cout << temp5 << endl; 

    
  // Part(a)

  cout << "Part(a) " << endl;
  double price=0;
  for(int i=0; i<NUM; ++i) {
    //cout << payoff[i] << endl; 
    price+=payoff[i]; 
  }
  price = price/NUM*exp(-r*T);
  //  cout << "Price of the option is : " << price << endl; 
  return 0;

}

