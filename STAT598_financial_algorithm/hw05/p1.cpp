#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#define NUM 3000

using namespace std;


class Rebalance{
public:
  double x0, S0, C0; 
  double value;
  Rebalance(double x0, double S0,double C0) {
    this->x0 = x0;
    this->S0 = S0;
    this->C0 = C0; 
  }
  ~Rebalance() {} 
}; 

double binaryStock(double S0, double u, double d, double p, int steps, Rebalance* R){
  unsigned seed = chrono::system_clock::now().time_since_epoch().count(); 
  default_random_engine generator(seed);
  bernoulli_distribution distribution(p);
  double S=R->S0; 

  double C=R->C0;
  double x=R->x0; 
  
  for(int i=0; i<steps; ++i){
    if(distribution(generator)) {
      S=S*u;
    }
    else S=S*d;

    C = 0.5*(x*S+C);
    x = C/S; 
    
  }
  R->value = C+x*S; 
  return S; 
}

void meanVar(vector<double> v, double * mean, double *var) {
  int num = v.size();
  double sum = 0; 
  for(int i=0; i< num; ++i) {
   sum += v[i]; 
  }
  *mean = sum/num;
  sum = 0; 
  for(int i=0; i<num; ++i) {
    sum += (v[i]-(*mean))*(v[i]-(*mean)); 
    //cout << sum << endl; 
  }
  *var = sum/num; 

}


int main() {
  double u=2;
  double d=0.5;
  double p=0.5;
  double S0 = 1;
  int steps = 20; 

  double Buyhold;
 
  vector<double> buyholdValue;
  vector<double> rebalanceValue; 
  double C0 = 0.5;
  double x0 =0.5;

  for(int i=0; i<NUM; ++i) {
    Rebalance R(x0, S0, C0); 
    double Buyhold = binaryStock(S0, u, d, p, steps, &R ); 
    buyholdValue.push_back(Buyhold); 
    cout << Buyhold << endl; 
  }

  double mean;
  double var; 
  meanVar(buyholdValue, &mean, &var); 

  cout << "E(U) = " << mean << endl;
  cout << "var(U) = " << var << endl; 

  for(int i=0; i<NUM; ++i) {
    Rebalance R(x0, S0, C0); 
    double Buyhold = binaryStock(S0, u, d, p, steps, &R ); 
    rebalanceValue.push_back(R.value); 

  }

  meanVar(rebalanceValue, &mean, &var); 

  cout << "E(V) = " << mean << endl;
  cout << "var(V) = " << var << endl; 

  return 0; 

}
