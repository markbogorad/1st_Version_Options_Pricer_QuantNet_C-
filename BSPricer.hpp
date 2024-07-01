// BSPricer.hpp
// Level 9 Group A
// 
// Black-Scholes Pricer: utiltiy class for Black-Scholes calculations
// Single Responsibility: Implement Black-Scholes calculation methods: Pricing for call/put, Put-Call parity pricing, Put-Call parity holding, Greeks
// 
// @file Option.hpp
// @author Mark Bogorad
// @version 1.0 02/04/2024
//
#ifndef BSPRICER_HPP
#define BSPRICER_HPP

#include "Option.hpp"
#include <iostream>

class BSPricer {
private:
    Option option; // Composition with otpion class to have access to S,K,r,T,sigma,b but not be derived from option. Did this because they don't have a clear relationship, i.e. BSPricer is not an "Option", its a pricing mechanism class. Could be a derived class of "Pricing Methods" in the future, where the dervided class passes functionality to other option pricing methods.

public:
// Canonical Header 
    BSPricer(); // Default constructor
    BSPricer(const Option& opt); // Constructor with Option object
    BSPricer(double S, double K, double r, double T, double sigma, double b, int option_type); // Parameterized constructor using option variables (composition again)
    ~BSPricer(); // Destructor
    BSPricer& operator=(const BSPricer& source); // Assignment operator

// Parameter sanity check function
    void checkParameters(double S, double K, double r, double T, double sigma, double b);

// Black-Scholes functions
    double d1(double S, double K, double r, double T, double sigma, double b) const; // BS D1 parameter
    double d2(double S, double K, double r, double T, double sigma, double b) const; //BS D2 parameter
    double CallPrice(double S, double K, double r, double T, double sigma, double b, int option_type) const;
    double PutPrice(double S, double K, double r, double T, double sigma, double b, int option_type) const;

// Put-call parity functions
    double PCP_CallPrice(double S, double K, double r, double T, double p) const; // Put-call parity (PCP) price for CALL (given put get call price)
    double PCP_PutPrice(double S, double K, double r, double T, double c) const; // Put-call parity price for PUT (given put get call)
    bool PCP_Check(double S, double K, double r, double T, double c, double p) const; // Check for put-call parity relationship holding  

// Greeks functions (not making a seperate class for these because they use BS pricing variables and are basically an extension of BS)
    // Delta
    double CallDelta(double S, double K, double r, double T, double sigma, double b) const; 
    double PutDelta(double S, double K, double r, double T, double sigma, double b) const;  
    // Gamma
    double Gamma(double S, double K, double r, double T, double sigma, double b) const; 

// Divided differences functions
    double DeltaApprox(double h) const; // Approximate Delta
    double GammaApprox(double h) const; // Approximate Gamma

// American option functions
    double y1(double K, double r, double sigma, double b) const;
    double y2(double K, double r, double sigma, double b) const;
    double AmericanCallPrice(double S, double K, double r, double sigma, double b, int option_type) const;
    double AmericanPutPrice(double S, double K, double r, double sigma, double b, int option_type) const;
};

#endif