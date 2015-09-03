#include <iostream> 

#define TOL 0.00001

double func(double x)  {
  return x*x*x +2*x*x -3*x -1 ; 

}

double bisect(double a, double b, double (*func)(double)) {
  double tol = TOL;
  double m; 
  while (b-a>TOL) {
    m = (a+b)/2; 
    
    if(func(m)*func(a)<0) 
      b =m; 
    else a =m; 
  }
  return m; 

}

int main() {
  std::cout << bisect(0, 3, func) << std::endl; 


  return 0; 
}
