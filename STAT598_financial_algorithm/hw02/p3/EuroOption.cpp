/*
 * EuroOption.cpp
 *
 *  Created on: Feb 13, 2015
 *      Author: cheng109
 */

#include "EuroOption.h"
#include <cmath>
#define SUCCESS 0;
#include <iostream>
using namespace std;

EuroOption::EuroOption() {
}

EuroOption::EuroOption(double S, double K, double T, double sigma, double r){
	this->S =S;
	this->K = K;
	this->T = T;
	this->sigma = sigma;
	this->r = r;

	this->d1 = (log(S/K)+(r+sigma*sigma*0.5)*T)/(sigma*sqrt(T));
	this->d2 = d1-sigma*sqrt(T);

	this->Nd1= normalCDF(d1);
	this->Nd2= normalCDF(d2);
}

void EuroOption::updatePrice() {
	this->putPrice = K*exp(-r*T)- S + (S*Nd1 - K*exp(-r*T)*Nd2);
	this->callPrice = S*Nd1 - K*exp(-r*T)*Nd2;
}

void EuroOption::updateDelta() {
	this->callDelta = this->Nd1;
	this->putDelta = this->Nd1-1;
}

void EuroOption::updateGamma() {
	this->callGamma = normalPDF(d1)/(S*sigma*sqrt(T));
	this->putGamma = this->callGamma;
}


ostream & operator<<(ostream & out, const EuroOption& o){
	out << "**** European Option ****" << endl;
	out << "Stock Price:    " << o.S << endl ;
	out << "Strike Price:   " << o.K << endl ;
	out << "Maturity Time:  " << o.T << endl ;
	out << "Volatility:     " << o.sigma << endl ;
	out << "Risk-free Rate: " << o.r << endl<<endl ;

	out << "* Put *" << endl;
	out << "Price:     " << o.putPrice << endl;
	out << "Delta:     " << o.putDelta << endl;
	out << "Gamma:     " << o.putGamma << endl << endl;

	out << "* Call *" << endl;
	out << "Price:     " << o.callPrice << endl;
	out << "Delta:     " << o.callDelta << endl;
	out << "Gamma:     " << o.callGamma << endl ;
	out << "*************************" << endl;
	return out;
}


EuroOption::~EuroOption() {
}

double normalPDF(double x) {
	return 1/sqrt(2*M_PI)*exp(-x*x*0.5);
}

double normalCDF(double x){
	double sum = x;
	double value = x;
	for (int i=1; i<200; i++) {
		value = value*x*x/(2*i+1);
		sum = sum + value;
	}
	return 1/sqrt(2*M_PI)*exp(-x*x*0.5)*sum+0.5;
}


double EuroOption::call_price(const double s) {
	return S * normalCDF((log(S/K)+(r+s*s*0.5)*T)/(s*sqrt(T)))
				-K*exp(-r*T)*normalCDF((log(S/K)+(r+s*s*0.5)*T)/(s*sqrt(T))-s*sqrt(T));
}

double getImplySigma(EuroOption option, double M_C, double left, double right, double epsilon){
	double x=0.5*(left + right);
	double y=option.call_price(x);

	do {
		if (y<M_C)
			left=x;
		if(y>M_C)
			right=x;
		x=0.5*(left+right);
		y=option.call_price(x);
	} while(fabs(y-M_C) > epsilon);
	return x;
}

int main() {
	EuroOption option(100, 100, 1, 0.25, 0.05);
	option.updatePrice();
	option.updateDelta();
	option.updateGamma();
	cout << option ;
	cout << "Implied volatility: "
		 <<  getImplySigma(option, 12.336, 0.1, 0.4, 0.0001) << endl;

	return SUCCESS;
}
