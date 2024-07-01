// Option.cpp
// Level 9 Group A
// 
// Implementation of option base class, details in HPP
//
// @file Option.hpp
// @author Mark Bogorad
// @version 1.0 
//

#include "Option.hpp"


// Canonical header file implementation:

// Default constructor
Option::Option() : S(1), K(1), r(0.01), T(1), sigma(0.1), option_type(1) {} // Initialzed to 1s for now because I can't divide by 0 in the formulae (spent 8 hours debugging this)

// Copy constructor
Option::Option(const Option& option) : S(option.S), K(option.K), r(option.r), T(option.T), sigma(option.sigma), option_type(option.option_type) {}

// Parameterized constructor
Option::Option(double S, double K, double r, double T, double sigma, double b, int option_type) : S(S), K(K), r(r), T(T), sigma(sigma), b(b), option_type(option_type) {}

// Virtual destructor
Option::~Option() {}

// Assignment operator
Option& Option::operator=(const Option& source) {
    if (this == &source) return *this; // Handle self-assignment

    S = source.S;
    K = source.K;
    r = source.r;
    T = source.T;
    sigma = source.sigma;
    option_type = source.option_type;

    return *this;
}


/*Option cloneParams(double S, double K, double r, double T, double sigma, double b) const {
    return new (S, K, r, T, sigma, b);
}*/

// Getters
double Option::getS() const { return S; }
double Option::getK() const { return K; }
double Option::getR() const { return r; }
double Option::getT() const { return T; }
double Option::getSigma() const { return sigma; }
double Option::getB() const { return b; }
int Option::getOptionType() const { return option_type; }

// Setters
void Option::setS(double S) { this->S = S; }
void Option::setK(double K) { this->K = K; }
void Option::setR(double r) { this->r = r; }
void Option::setT(double T) { this->T = T; }
void Option::setSigma(double sigma) { this->sigma = sigma; }
void Option::setB(double b) { this->b = b; }
void Option::setOptionType(int option_type) { this->option_type = option_type; }


// Price will be implemented within indivudal option type

// Toggle function
void Option::toggle() {
	if (option_type == 1) {
		option_type = 2; // If its a call (1), switch it to put (2)
	}
	else {
		option_type = 1; // Otherwise (only 1 other option), switch it to call
	}
	return;
}
