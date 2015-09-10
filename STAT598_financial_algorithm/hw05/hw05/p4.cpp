#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#define NUM 1000
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
  // v is an independent d-dimensional random normal.
  vector<double> corrZ(d, 0); 
  for(int i=0; i<d; ++i) {
    for(int j=0; j<d; ++j) {
      corrZ[i]+=A[i][j]*v[j];
    }
  }
  return corrZ; 
}

double payoffFunc_X(vector<double> ST, int d, double K) {
  double payoff=0;
  for(int i=0; i<d; ++i)
    payoff+=ST[i]; 
  if (payoff>K)
    return payoff-K;
  return 0; 
}

double payoffFunc_Y(vector<double> ST, int d, double K) {
  double payoff=1;
  for(int i=0; i<d; ++i)
    payoff*=ST[i];
  payoff = d*pow(payoff,1.0/d); 
  if (payoff>K)
    return payoff-K;
  return 0; 
}

double payoffFunc_VarCtrl(double payoff_X, double payoff_Y, double b) {
  return payoff_X-b*(payoff_Y-52.45); 
}



int main() {
  int d = 10;
  matrix cov = iniMatrix(d);
  double sigma = 0.15;
  double rho = 0.3;
 
  for (int i=0; i<d; ++i) {
    for (int j=0; j<d; ++j) {
      if(i==j) cov[i][j]= sigma*sigma; 
      if(i!=j) cov[i][j]= rho*sigma*sigma; 
    }
  }
  //printMatrix(cov, d); 
  matrix A = Cholesky(cov, d);
  //printMatrix(A, d); 

  unsigned seed = chrono::system_clock::now().time_since_epoch().count();
  default_random_engine generator(seed);
  normal_distribution<double> distribution(0,1);

  for(int count=0; count<1000; count++) {
  double T =1; 
  double K=100*d;
  int steps = 500;
  double dt = T/steps; 
  double r=0.04; 
  double S0 =100; 
  vector<double> payoff_X(NUM, 0); 
  vector<double> payoff_Y(NUM, 0);
  vector<double> payoff_VarCtrl(NUM, 0); 
  double sumPayoff_X=0;
  double sumPayoff_Y=0; 
  double sumPayoff_VarCtrl=0; 
  for (int t= 0; t<NUM;++t) {
    vector<double> stock(d, S0);
    double sumStock=0;
    for (int step=0; step<steps; ++step) { 
      vector<double> v; 
      for(int i=0; i<d; i++) {
	double Z = distribution(generator);
	v.push_back(Z);
      }
      vector<double> corrZ =  correlatedGDB(d, A, v );
      for(int i=0; i<d; ++i) {
	stock[i]= stock[i] + stock[i]*r*dt+stock[i]*sqrt(dt)*corrZ[i] + 0.5*(corrZ[i]*corrZ[i]-sigma*sigma)*dt;
	if(step==steps-1 )
	  sumStock += stock[i]; 
      }
    }
    payoff_X[t] = payoffFunc_X(stock, d, K);
    payoff_Y[t] = payoffFunc_Y(stock, d, K);
    payoff_VarCtrl[t]=payoffFunc_VarCtrl(payoff_X[t], payoff_Y[t], 1.037); 
    sumPayoff_X+= payoffFunc_X(stock, d, K);
    sumPayoff_Y+= payoffFunc_Y(stock, d, K);
    sumPayoff_VarCtrl += payoff_VarCtrl[t]; 
  }
  Part(a)
  cout << "Part(a) " << endl;
  cout << "Price is : " << sumPayoff_X/NUM*exp(-r*T) << endl; 


  // Part(d)
  // To get the optimal b*
  /* double avg_X=sumPayoff_X/NUM;
  double avg_Y=sumPayoff_Y/NUM; 
  double sum_1=0;
  double sum_2=0; 
  for(int i=0; i<NUM; ++i) {
    sum_1+=(payoff_X[i]-avg_X)*(payoff_Y[i]-avg_Y);
    sum_2+=(payoff_Y[i]-avg_Y)*(payoff_Y[i]-avg_Y);
  }
  */
  //double b = sum_1/sum_2;
  //cout << "Part(d)" << endl; 
  //cout << "Optimal b = " << b << endl;
  cout << count<< "\t" <<  sumPayoff_X/NUM*exp(-r*T) << "\t" <<  sumPayoff_VarCtrl/NUM*exp(-r*T) << endl; 

  }
  return 0;
  
}

