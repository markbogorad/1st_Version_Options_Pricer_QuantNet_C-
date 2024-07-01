// BSPricer.cpp
// Level 9 Group A
// 
// Implementation of BSPricer
//
// @file Option.hpp
// @author Mark Bogorad
// @version 1.0 02/04/2024
//
#include "BSPricer.hpp"
#include "Option.hpp"
#include <cmath>
#include <boost/math/distributions/normal.hpp>

using namespace boost::math;

// Canonical header
// Default constructor
BSPricer::BSPricer() : option() {}

// Constructor with Option object
BSPricer::BSPricer(const Option& opt) : option(opt) {}

// Parameterized constructor
BSPricer::BSPricer(double S, double K, double r, double T, double sigma, double b, int option_type) : option(S, K, r, T, sigma, b, option_type) {} 

// Destructor
BSPricer::~BSPricer() {}

// Copy assignment operator
BSPricer& BSPricer::operator=(const BSPricer& source) {
    if (this != &source) { // Prevent self-assignment
        option = source.option; 
    }
    return *this;
}

void BSPricer::checkParameters(double S, double K, double r, double T, double sigma, double b) {
    // Check for NaN
    if (std::isnan(S) || std::isnan(K) || std::isnan(r) || std::isnan(T) || std::isnan(sigma) || std::isnan(b)) {
        throw std::invalid_argument("One or more parameters are NaN");
    }

    // Check for infinity
    if (std::isinf(S) || std::isinf(K) || std::isinf(r) || std::isinf(T) || std::isinf(sigma) || std::isinf(b)) {
        throw std::invalid_argument("One or more parameters are infinity");
    }

    // Check for non-positive values where not allowed
    if (S <= 0 || K <= 0 || T <= 0 || sigma <= 0) {
        throw std::invalid_argument("S, K, T, and sigma must be positive");
    }

    // Check realistic ranges
    if (r < 0 || r > 1 || b < 0 || b > 1) {
        throw std::invalid_argument("r and b must be between 0 and 1");
    }
    if (std::isnan(S) || std::isnan(K) || std::isnan(r) || std::isnan(T) || std::isnan(sigma) || std::isnan(b)) {
        throw std::invalid_argument("Error: One or more parameters are NaN");
    }
    if (std::isinf(S) || std::isinf(K) || std::isinf(r) || std::isinf(T) || std::isinf(sigma) || std::isinf(b)) {
        throw std::invalid_argument("Error: One or more parameters are infinity");
    }
    if (S <= 0) throw std::invalid_argument("Error: S must be positive");
    if (K <= 0) throw std::invalid_argument("Error: K must be positive");
    if (T <= 0) throw std::invalid_argument("Error: T must be positive");
    if (sigma <= 0) throw std::invalid_argument("Error: sigma must be positive");
    if (r < 0 || r > 1) throw std::invalid_argument("Error: r must be between 0 and 1");
    if (b < 0 || b > 1) throw std::invalid_argument("Error: b must be between 0 and 1");
}

// BS Pricing Functions:

// D1 and D2 initalized at start to be used in Black Scholes formulae below and in the Greeks implementation
// D1:
double BSPricer::d1 (double S, double K, double r, double T, double sigma, double b) const {
    return (log(S / K) + (b + (sigma * sigma) * 0.5) * T) / (sigma * sqrt(T));
}

// D2:
double BSPricer::d2 (double S, double K, double r, double T, double sigma, double b) const {

    double d1Value = d1(S, K, r, T, sigma, b); // Using d1Value for modularity and to make negative in put pricing (can't directly change scope of variable)
    return d1Value - (sigma * sqrt(T));
} 

// Black-Scholes Call Price
double BSPricer::CallPrice(double S, double K, double r, double T, double sigma, double b, int option_type) const {
    double d1Value = d1(S, K, r, T, sigma, b);
    double d2Value = d2(S, K, r, T, sigma, b);

    normal_distribution<> N(0, 1);
    return (S * exp((b - r) * T) * cdf(N, d1Value)) - (K * exp(-r * T) * cdf(N, d2Value));
}

// Black-Scholes Put Price
double BSPricer::PutPrice(double S, double K, double r, double T, double sigma, double b, int option_type) const {
    
    double d1Value = d1(S, K, r, T, sigma, b);
    double d2Value = d2(S, K, r, T, sigma, b);
    normal_distribution<> N(0, 1);
    
    return (K * exp(-r * T) * cdf(N, -d2Value)) - (S * exp((b - r) * T) * cdf(N, -d1Value));
}

// Put-Call Parity pricing methods:
// Use put-call parity to calculate call price
double BSPricer::PCP_CallPrice(double S, double K, double r, double T, double p) const {
	return p + S - K * exp(-r * T); // Uses put (p) in calculation
}

// Use put-call parity to calculate put price
double BSPricer::PCP_PutPrice(double S, double K, double r, double T, double c) const { 
	return c + K * exp(-r * T) - S; // Uses call (c) in calculation
}

// Function to check if pcp holds
bool BSPricer::PCP_Check(double S, double K, double r, double T, double c, double p) const {
    double LHS = c + K * exp(-r * T); // Left hand side of Put-Call parity equation
    double RHS = p + S; // Right hand side of Put-Call parity equation
    const double Tolerance = 0.01; // Tolerance for rounding errors and other slight impercisions

    bool ParityHolds = std::abs(LHS - RHS) < Tolerance;
    if (ParityHolds) {
        std::cout << "Put-Call Parity Holds" << std::endl;
        return true;
    } else {
        std::cout << "Put-Call Parity doesn't hold!!" << std::endl;
        return false;
    }
}

// Delta for a Call option
double BSPricer::CallDelta(double S, double K, double r, double T, double sigma, double b) const {
    normal_distribution<> N(0, 1);
    double d1Value = d1(S, K, r, T, sigma, b);
    return exp((b - r) * T) * cdf(N, d1Value);
}

// Delta for a Put option
double BSPricer::PutDelta(double S, double K, double r, double T, double sigma, double b) const {
    normal_distribution<> N(0, 1);
    double d1Value = d1(S, K, r, T, sigma, b);
    return exp((b - r) * T) * (cdf(N, d1Value) - 1); // Key difference
}

// Gamma for both Call and Put options (Gamma is the same for both)
double BSPricer::Gamma(double S, double K, double r, double T, double sigma, double b) const {
    normal_distribution<> N(0, 1);
    double d1Value = d1(S, K, r, T, sigma, b);
    return pdf(N, d1Value) * exp((b - r) * T) / (S * sigma * sqrt(T));
}

double BSPricer::DeltaApprox(double h) const {
    // Calculate the option price for S + h
    double priceUp = this->CallPrice(option.S + h, option.K, option.r, option.T, option.sigma, option.b, option.option_type); // This is (V(S+h))
    // Calculate the option price for S - h
    double priceDown = this->CallPrice(option.S - h, option.K, option.r, option.T, option.sigma, option.b, option.option_type); // This is (V(S-h))
    // Compute the Delta approximation
    return (priceUp - priceDown) / (2 * h); // Formula for delta approximation
}

double BSPricer::GammaApprox(double h) const {
    // Calculate the option price for S + h
    double priceUp = this->CallPrice(option.S + h, option.K, option.r, option.T, option.sigma, option.b, option.option_type);
    // Calculate the option price for S
    double price = this->CallPrice(option.S, option.K, option.r, option.T, option.sigma, option.b, option.option_type);
    // Calculate the option price for S - h
    double priceDown = this->CallPrice(option.S - h, option.K, option.r, option.T, option.sigma, option.b, option.option_type);
    // Compute the Gamma approximation
    return (priceUp - 2 * price + priceDown) / (h * h);
}



// American option pricers:

// Y1 variable (for call)
double BSPricer::y1(double K, double r, double sigma, double b) const {
    return (0.5 - (b / (sigma * sigma)) + sqrt(pow((b / (sigma * sigma) - 0.5), 2) + (2 * r) / (sigma * sigma)));
}

// Y2 variable (for put)
double BSPricer::y2(double K, double r, double sigma, double b) const {
    return (0.5 - (b / (sigma * sigma)) - sqrt(pow((b / (sigma * sigma) - 0.5), 2) + (2 * r) / (sigma * sigma)));
}

// American Call Price
double BSPricer::AmericanCallPrice(double S, double K, double r, double sigma, double b, int option_type) const {
    double y1Value = y1(K, r, sigma, b);
    return ( (K / (y1Value - 1.0)) * pow(((y1Value - 1.0) / y1Value) * (S / K), y1Value) );
}

// American Put Price
double BSPricer::AmericanPutPrice(double S, double K, double r, double sigma, double b, int option_type) const {
    double y2Value = y2(K, r, sigma, b);
    return ( (K / (1.0-y2Value)) * pow(((y2Value - 1.0) / y2Value) * (S / K), y2Value) );
    
}