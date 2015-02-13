/*
 * EuroOption.h
 *
 *  Created on: Feb 13, 2015
 *      Author: cheng109
 */

#ifndef EUROOPTION_H_
#define EUROOPTION_H_
#include <iostream>
using namespace std;
class EuroOption {
private:
	double S;
	double K;
	double T;
	double sigma;
	double implySigma;
	double r;

	double d1;
	double d2;
	double Nd1;
	double Nd2;

public:
	double putPrice;
	double callPrice;

	double putDelta;
	double callDelta;

	double putGamma;
	double callGamma;

public:
	EuroOption();
	EuroOption(double S, double K, double T, double sigma, double r);
	void updatePrice();
	void updateDelta();
	void updateGamma();
	friend ostream & operator<<(ostream & out, const EuroOption& option);
	double call_price(const double sigma);
	double operator()(double sigma) const;
	virtual ~EuroOption();
};

double getImplySigma(EuroOption o, double M_C, double left, double right, double epsilon);
double normalCDF(double x);
double normalPDF(double x) ;
#endif /* EUROOPTION_H_ */
