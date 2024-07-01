// EuropeanOption.hpp
// Level 9 Group A
// 
// EuropeanOption pricing class, derived from Option.
// Single Responsibility: Implement Black-Scholes pricing for European options
//
// @file EuropeanOption.hpp
// @author Mark Bogorad
// @version 1.0 
//
#include "Option.hpp"
#include "BSPricer.hpp"


#ifndef EUROPEANOPTION_HPP
#define EUROPEANOPTION_HPP

#include <iostream>

class EuropeanOption : public Option {
private:
    std::shared_ptr<BSPricer> BS; // Smart pointer (for automatic memory managment) to an instance of BSPricer where the actual Black-Scholes equation is
public:
// Canonical Header
    EuropeanOption(); // Default constructor
    EuropeanOption(const EuropeanOption& option); // Copy constructor
    EuropeanOption(double S, double K, double r, double T, double sigma, double b, int option_type); // Parameterized constructor
    virtual ~EuropeanOption(); // Virtual destructor
    EuropeanOption& operator=(const EuropeanOption& source);// Assignment operator
// Overrided getters and setters from option base

     // Overloaded getters
    double getS() const override;
    double getK() const override;
    double getR() const override;
    double getT() const override;
    double getSigma() const override;
    double getB() const override;
    int getOptionType() const override;
    
    // Overloaded setters
    void setS(double S) override;
    void setK(double K) override;
    void setR(double r) override;
    void setT(double T) override;
    void setSigma(double sigma) override;
    void setB(double b) override;
    void setOptionType(int option_type) override;

   
// BS Pricing functions 
    double Price() const; // Overrided from option base
    double PCP_Price() const;
    double DividedDifferences() const;

 // Inheriting constructors
    using Option::Option;

    
};

#endif