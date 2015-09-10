#include <iostream>
#include <cmath> 
#include <random> 
#include <chrono>
#define NUM 1000000
using namespace std;


/* This fucntion "phi" is copied from internet */
double phi(double x)
{
  static const double RT2PI = sqrt(4.0*acos(0.0));
  static const double SPLIT = 7.07106781186547;
  static const double N0 = 220.206867912376;
  static const double N1 = 221.213596169931;
  static const double N2 = 112.079291497871;
  static const double N3 = 33.912866078383;
  static const double N4 = 6.37396220353165;
  static const double N5 = 0.700383064443688;
  static const double N6 = 3.52624965998911e-02;
  static const double M0 = 440.413735824752;
  static const double M1 = 793.826512519948;
  static const double M2 = 637.333633378831;
  static const double M3 = 296.564248779674;
  static const double M4 = 86.7807322029461;
  static const double M5 = 16.064177579207;
  static const double M6 = 1.75566716318264;
  static const double M7 = 8.83883476483184e-02;

  const double z = fabs(x);
  double c = 0.0;

  if(z<=37.0)
    {
      const double e = exp(-z*z/2.0);
      if(z<SPLIT)
	{
	  const double n = (((((N6*z + N5)*z + N4)*z + N3)*z + N2)*z + N1)*z + N0;
	  const double d = ((((((M7*z + M6)*z + M5)*z + M4)*z + M3)*z + M2)*z + M1)*z + M0;
	  c = e*n/d;
	}
      else
	{
	  const double f = z + 1.0/(z + 2.0/(z + 3.0/(z + 4.0/(z + 13.0/20.0))));
	  c = e/(RT2PI*f);
	}
    }
  return x<=0.0 ? c : 1-c;
}


void meanVar(vector<double> v, double * mean, double *var) {
  int num = v.size();
  double sum = 0;
  for(int i=0; i< num; ++i) {
    sum += v[i];
  }
  *mean = sum/num;
  sum = 0;
  for(int i=0; i<num; ++i)
    sum += (v[i]-(*mean))*(v[i]-(*mean));
  *var = sum/num;
}


class Option{
public:
  double mu;
  double sigma;
  double r;
  double K;
  double S0;
  double T;
  double price; 
  Option(double mu, double sigma, double K, double r, double S0, double T):mu(mu),sigma(sigma),r(r), K(K),S0(S0),T(T) {
  }; 
  double getPrice(double t, double S); 
  double getDelta(double t, double S); 
  //~Option(); 
};

double Option::getPrice(double t, double S) {
  double d1 = 1/(this->sigma*sqrt(this->T-t))*(log(S/this->K)+(this->r+this->sigma*this->sigma/2)*(this->T-t));
  double d2 = d1-this->sigma*sqrt(this->T-t);
  return phi(d1)*S-phi(d2)*K*exp(-this->r*(this->T-t)); 
}
double Option::getDelta(double t, double S) {
  double d1 = 1/(this->sigma*sqrt(this->T-t))*(log(S/this->K)+(this->r+this->sigma*this->sigma/2)*(this->T-t));
  return phi(d1); 
}


vector<double> simStockPrice(Option option, double dt, int num) {
  // Euler scheme
  vector<double> v;
  unsigned seed = chrono::system_clock::now().time_since_epoch().count(); 
  default_random_engine generator(seed); 
  normal_distribution<double> distribution(0,1);
  double S = option.S0;
  for(int i=0; i<num; ++i) {
    double Z = distribution(generator); 
    S = S*exp((option.r-0.5*option.sigma*option.sigma)*dt+option.sigma*sqrt(dt)*Z); 
    v.push_back(S); 
  }
  return v ; 
}

double payoff_Func(vector<double> stock, int steps, double K, double H) {
  for(int i=0; i<steps; ++i) {
    if(stock[i]> H)
      return 0;
  }
  if (stock[steps-1]>K)
    return 0; 
  return K-stock[steps-1]; 

}


double new_payoff_Func(vector<double> stock, int steps, double K, double H, double dt, Option option) {
  double q=0; 
  if(stock[steps-1]<H && option.S0<H)
    q= exp(2/(option.sigma*option.sigma)/option.T*log(H/option.S0)*log(stock[steps-1]/H)); 
  //cout << q << endl; 
  if (stock[steps-1]>K)
    return 0; 
  return (K-stock[steps-1])*(1-q); 

}

int main() {
  double sigma = 0.3;
  double r = 0.05;
  double K = 60;
  double S0= 50; 
  double H = 55;

  double mu = 0.1; 
  double dt = 1.0/365; 
  
  int n = floor(0.25/dt); 
  vector<double> error; 
  double T = n*dt; 
  Option option(mu, sigma, K, r, S0, T);
  double price = option.getPrice(0,S0); 

  vector<double> payoff(NUM, 0); 
  vector<double> new_payoff(NUM, 0); 
  for (int j=0; j<NUM; ++j) {
    double numShare=0; 
    double account = 0;
    vector<double> v = simStockPrice(option, dt, n);
    payoff[j] = payoff_Func(v, n, K, H);
    new_payoff[j]=new_payoff_Func(v, n, K, H, dt, option) ; 
  }
  
  double mean;
  double var; 
  cout << "Part (a)" << endl; 
  meanVar(payoff, &mean, &var);
  cout << "E(X)= " << mean*exp(-r*T) << endl;
  cout << "std(X)= " << sqrt(var) << endl;
  cout << "95% confidence interval: " << 2*1.96*sqrt(var)/sqrt(NUM) << endl; 

  cout << "Part(b)" << endl; 
  meanVar(new_payoff, &mean, &var);
  cout << "E(X)= " << mean*exp(-r*T) << endl;
  cout << "std(X)= " << sqrt(var) << endl;
  cout << "95% confidence interval: " << 2*1.96*sqrt(var)/sqrt(NUM) << endl; 

  return 0;
}

