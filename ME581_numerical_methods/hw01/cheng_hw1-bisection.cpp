#include <iostream> 
#include <cmath>
#define TOL 0.00001

// Problem 1
double func1(double x)  {
  return exp(-x)-x; 
}

double func2(double x) {
  return pow(x,6)-3; 
}

// Problem 5
double func5(double x) {
  return x*x*x-13;
}

double func6(double x) {
  return tan(M_PI*x)-x-6; 
}
double bisect(double a, double b, double (*func)(double)) {
  double p = 1.45757030926; 
  double tol = TOL;
  double m;
  int iter = 0; 
  while (b-a>TOL) {
 
    m = (a+b)/2; 
    
    if(func(m)*func(a)<0) 
      b =m; 
    else a =m;
    iter ++; 
    std::cout << iter << "\t" << m << "\t" << std::abs(m-p) << std::endl;
    
  }
  
  return m; 

}

int main() {
  double (*func)(double) = &func1; 
  //std::cout << bisect(0, 1, func1) << std::endl; 
  std::cout << bisect(1.0,1.49, func6) << std::endl; 
  
  return 0; 
}
