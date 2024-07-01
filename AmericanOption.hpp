// AmericanOption.hpp
// Level 9 Group A
// 
// American Option pricing class, derived from Option.
// Single Responsibility: Implement American option pricing formulae.
//
// @file EuropeanOption.hpp
// @author Mark Bogorad
// @version 1.0 
//
#ifndef AMERICANOPTION_HPP
#define AMERICANOPTION_HPP

#include "Option.hpp"
#include "BSPricer.hpp"
#include <iostream>

class AmericanOption : public Option {
private:
    std::shared_ptr<BSPricer> Ameri; // Smart pointer to ABS American Black-Scholes functions in BSPricer

public:
// Canonical Header
    AmericanOption(); // Default constructor
    AmericanOption(const AmericanOption& option); // Copy constructor
    AmericanOption(double S, double K, double r, double sigma, double b, int option_type); // Parameterized constructor (T included to match with base class)
    virtual ~AmericanOption(); // Virtual destructor
    AmericanOption& operator=(const AmericanOption& source);// Assignment operator
// Pricing functions:
    double Price(); // Overrided from option base
// Overrided getters and setters from option base
     // Overloaded getters
    double getS() const override;
    double getK() const override;
    double getR() const override;
    double getSigma() const override;
    double getB() const override;
    int getOptionType() const override;
    
    // Overloaded setters
    void setS(double S) override;
    void setK(double K) override;
    void setR(double r) override;
    void setSigma(double sigma) override;
    void setB(double b) override;
    void setOptionType(int option_type) override;

};

#endif