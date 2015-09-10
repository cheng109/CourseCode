#include <iostream>
#include <cmath>

#define TOL 0.000001
// Problem 4
double func4(double x) {
  return pow(x,3)+pow(x,2)-3*x-3; 
}

double func4dev(double x) {
  return pow(x,2)*3 +2*x-3; 
}

double ff(double x) {
  return (6*x+2)/(6*x*x+4*x-6); 
}

double func7a(double x) {
  return exp(x)+x*x-x-4; 
}

double func7b(double x) {
  return pow(x,3)-x*x-10*x+7; 
}

double func7c(double x) {
  return 1.05-1.04*x+log(x); 
}

double func7adev(double x) {
  return exp(x)+2*x-1; 
}

double func7bdev(double x) {
  return 3*pow(x,2)-2*x-10; 
}

double func7cdev(double x) {
  return -1.04+1.0/x; 
}


double newton(double a, double (*func)(double), double (*funcdev)(double)) {
  // starting point a;
  double p = sqrt(3); 
  double temp; 
  do{
    temp = a; 
    a = a-func(a)/funcdev(a);
    std::cout <<  std::abs(a-temp)  << "\t" << std::abs(temp -p) << "\t" << std::abs(a-p) << std::endl;
    long double ld = std::abs(a-p)/pow(std::abs(temp -p),2); 
    //std::cout << ld  << "\t" << ff(p) << std::endl; 
  }while(std::abs(a-temp)>TOL); 
  return a; 
}

int main() {
  double (*f4)(double) = &(func4);
  double (*fd4)(double) = &(func4dev) ; 
  std::cout << newton(1.0, func7a, func7adev) << std::endl;
  std::cout << newton(1.0, func7b, func7bdev) << std::endl;
  std::cout << newton(1.0, func7c, func7cdev) << std::endl; 

  return 0;

}
