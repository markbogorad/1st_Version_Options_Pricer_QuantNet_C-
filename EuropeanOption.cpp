// EuropeanOption.cpp
// Level 9 Group A
// 
// Implementation of European Option class
//
// @file Option.hpp
// @author Mark Bogorad
// @version 1.0 
//

#include "Option.hpp"
#include "EuropeanOption.hpp"
#include "BSPricer.hpp"
#include <boost/shared_ptr.hpp>
#include <memory>
//Canonical Header:

// Default constructor
EuropeanOption::EuropeanOption() : Option(), BS(std::make_shared<BSPricer>()) {}

// Copy constructor
EuropeanOption::EuropeanOption(const EuropeanOption& option) : Option(), BS(option.BS) {}

// Parameterized constructor with option base class variables
EuropeanOption::EuropeanOption(double S, double K, double r, double T, double sigma, double b, int option_type) : Option(S, K, r, T, sigma, b, option_type), BS(std::make_shared<BSPricer>()) {}

// Destructor
EuropeanOption::~EuropeanOption() {}

// Assignment operator
EuropeanOption& EuropeanOption::operator=(const EuropeanOption& source) {
    if (this == &source) return *this; // Handle self-assignment
    BS = source.BS;
    
    return *this;
}


// Overloaded setters
void EuropeanOption::setS(double S) {
    // Specific validation or adjustment for EuropeanOption
    Option::setS(S);
}

void EuropeanOption::setK(double K) {
    Option::setK(K);
}

void EuropeanOption::setR(double r) {
    Option::setR(r);
}

void EuropeanOption::setT(double T) {
    Option::setT(T);
}

void EuropeanOption::setSigma(double sigma) {
    Option::setSigma(sigma);
}

void EuropeanOption::setB(double b) {
    Option::setB(b);
}

void EuropeanOption::setOptionType(int option_type) {
    Option::setOptionType(option_type);
}

// Overloaded getters
double EuropeanOption::getS() const {
    return Option::getS();
}

double EuropeanOption::getK() const {
    return Option::getK();
}

double EuropeanOption::getR() const {
    return Option::getR();
}

double EuropeanOption::getT() const {
    return Option::getT();
}

double EuropeanOption::getSigma() const {
    return Option::getSigma();
}

double EuropeanOption::getB() const {
    return Option::getB();
}

int EuropeanOption::getOptionType() const {
    return Option::getOptionType();
}


// Option Price
double EuropeanOption::Price() const {
    // Sanity check
    if (S <= 0 || K <= 0 || sigma <= 0 || T <= 0) {
        throw std::domain_error("Invalid input: All input values must be positive.");
    }
    // Then point to BSPricer to calculate the price
    if (option_type == 1) {
        return BS->CallPrice(S, K, r, T, sigma, b, option_type);
    } else if (option_type == 2) {
        return BS->PutPrice(S, K, r, T, sigma, b, option_type);
    }
    else {
        throw std::domain_error("Select 1 for call 2 for put"); // Throw error if neither 1 or 2 is selected
    }
}

double EuropeanOption::PCP_Price() const {
    // Sanity check
    if (S <= 0 || K <= 0 || sigma <= 0 || T <= 0) {
        throw std::domain_error("Invalid input: All input values must be positive.");
    }

     // Calculate call and put prices directly using BSPricer. Needed 
    double c = BS->CallPrice(S, K, r, T, sigma, b, option_type);
    double p = BS->PutPrice(S, K, r, T, sigma, b, option_type);

    // Use put-call parity to check or calculate the other price
    // Assuming option_type indicates which price to return based on PCP
    if (option_type == 1) {
        // Calculate and return put price from known call price using PCP formula
        return BS->PCP_CallPrice(S, K, r, T, p);
    } else if (option_type == 2) {
        // Calculate and return call price from known put price using PCP formula
        return BS->PCP_PutPrice(S, K, r, T, c);
    }
    else {
        throw std::domain_error("Select 1 for call 2 for put");
    }
}

