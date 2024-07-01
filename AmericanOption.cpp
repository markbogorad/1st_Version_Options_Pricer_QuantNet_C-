// AmericanOption.hpp
// Level 9 Group A
// 
// American Option implementation
//
// @file EuropeanOption.hpp
// @author Mark Bogorad
// @version 1.0 
//
#include "AmericanOption.hpp"

// Canonical header
AmericanOption::AmericanOption() : Option() {} // Default constructor
AmericanOption::AmericanOption(const AmericanOption& option) : Option(option) {} // Copy constructor
AmericanOption::AmericanOption(double S, double K, double r, double sigma, double b, int option_type) : Option(S, K, r, T, sigma, b, option_type) {} // Parameterized constructor (T is included to match option but won't be used)
AmericanOption::~AmericanOption() {}// Virtual destructor
AmericanOption& AmericanOption::operator=(const AmericanOption& source) { // Assignment operator
    if (this != &source) { // Protect against self-assignment
        Option::operator=(source); // Assign base class parts
        // Copy state
    }
    return *this;
}

// Pricing function
double AmericanOption::Price() {
  // Sanity check
    if (S <= 0 || K <= 0 || sigma <= 0 || T <= 0) {
        throw std::domain_error("Invalid input: All input values must be positive.");
    }
    // If passed, point to pricing formulae in BSPricer
    if (option_type == 1) {
        return Ameri->AmericanCallPrice(S, K, r, sigma, b, option_type);
    } else if (option_type == 2) {
        return Ameri->AmericanPutPrice(S, K, r, sigma, b, option_type);
    }
    else {
        throw std::domain_error("Select 1 for call 2 for put");
    }
}

// Getters
double AmericanOption::getS() const { return Option::getS(); }
double AmericanOption::getK() const { return Option::getK(); }
double AmericanOption::getR() const { return Option::getR(); }
double AmericanOption::getSigma() const { return Option::getSigma(); }
double AmericanOption::getB() const { return Option::getB(); }
int AmericanOption::getOptionType() const { return Option::getOptionType(); }

// Setters
void AmericanOption::setS(double S) { Option::setS(S); }
void AmericanOption::setK(double K) { Option::setK(K); }
void AmericanOption::setR(double r) { Option::setR(r); }
void AmericanOption::setSigma(double sigma) { Option::setSigma(sigma); }
void AmericanOption::setB(double b) { Option::setB(b); }
void AmericanOption::setOptionType(int option_type) { Option::setOptionType(option_type); }
