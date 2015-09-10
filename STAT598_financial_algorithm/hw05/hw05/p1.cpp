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
  int steps = 19; 

  vector<double> buyholdValue;
  vector<double> rebalanceValue; 
  double C0 = 0.5;
  double x0 =0.5;

  // Part (a)
  for(int i=0; i<NUM; ++i) {
    Rebalance R(x0, S0, C0); 
    double Buyhold = binaryStock(S0, u, d, p, steps, &R ); 
    buyholdValue.push_back(Buyhold); 
  }
  double mean;
  double var; 
  meanVar(buyholdValue, &mean, &var); 
  cout << "Part(a)" << endl; 
  cout << "E(U) = " << mean << endl;
  cout << "var(U) = " << var << endl;
  cout << "95% confidence interval: [" << mean-1.96*sqrt(var/NUM) << ", " << mean+1.96*sqrt(var/NUM)<< "]" << endl;  
  cout << "===========================" << endl ; 

  double mean1;
  double var1;
  for(int i=0; i<NUM; ++i) {
    Rebalance R(x0, S0, C0); 
    binaryStock(S0, u, d, p, steps, &R ); 
    rebalanceValue.push_back(R.value); 

  }
  meanVar(rebalanceValue, &mean1, &var1); 
  cout << "E(V) = " << mean1 << endl;
  cout << "var(V) = " << var1 << endl; 
  cout << "95% confidence interval: [" << mean1-1.96*sqrt(var1/NUM) << ", " << mean1+1.96*sqrt(var1/NUM)<< "]" << endl;  
  cout << "==========================="<< endl ; 

  // Part(b)
  cout <<"Part(b)"<< endl; 
  double meanT=mean1-mean;
  double varT= var1+var; 
  cout << "E(T) = " << meanT << endl;
  cout << "var(T) = " << varT << endl;
  cout << "95% confidence interval: [" << meanT-1.96*sqrt(varT/NUM) << ", " << meanT+1.96*sqrt(varT/NUM)<< "]" << endl;
    cout << "==========================="<< endl ; 

  // Part(c)

  vector<double> diff; 
  double newMean;
  double newVar;
  for(int i=0; i<NUM; ++i) {
    Rebalance R(x0, S0, C0); 
    double buyhold = binaryStock(S0, u, d, p, steps, &R ); 
    diff.push_back(R.value-buyhold); 
  }
  meanVar(diff, &newMean, &newVar); 
  cout <<"Part(c)"<< endl; 

  cout << "E(V-U) = " << newMean << endl;
  cout << "var(V-U) = " << newVar << endl;
  cout << "95% confidence interval: [" << newMean-1.96*sqrt(newVar/NUM) << ", " << newMean+1.96*sqrt(newVar/NUM)<< "]" << endl;
  cout << "==========================="<< endl ;   


  // Part (d)


  vector<double> logFunc; 
  double logMean;
  double logVar;
  for(int i=0; i<NUM; ++i) {
    Rebalance R(x0, S0, C0); 
    double buyhold = binaryStock(S0, u, d, p, steps, &R ); 
    logFunc.push_back(log10(R.value)-log10(buyhold)); 
  }
  meanVar(logFunc, &logMean, &logVar); 
  cout <<"Part(d)"<< endl; 

  cout << "E(logV-logU) = " << logMean << endl;
  cout << "var(logV-logU) = " << logVar << endl;
  cout << "95% confidence interval: [" << logMean-1.96*sqrt(logVar/NUM) << ", " << logMean+1.96*sqrt(logVar/NUM)<< "]" << endl;
  cout << "==========================="<< endl ;   
  

  return 0;
}
