// Option.hpp
// Level 9 Group A
// 
// Option base class. 
// Single Responsibility: Serve as the base class for different option types, holding key option parameters
// 
// @file Option.hpp
// @author Mark Bogorad
// @version 1.0 
//

#ifndef OPTION_HPP
#define OPTION_HPP

#include <iostream>

class Option {
protected: // Protected to share this with inherited classes
// Black-Scholes variables (used in various types of pricing)
    double S; // Underlying asset price
    double K; // Strike price
    double r; // Risk-free rate
    double T; // Time to maturity in years
    double sigma; // Volatility
    double b; // Cost of carry
    int option_type; // 1 for call 2 for put (to be implemented)

public: 
// Canonical header
    Option(); // Default constructor
    Option(const Option& option); // Copy constructor
    Option(double S, double K, double r, double T, double sigma, double b, int option_type); // Parameterized constructor
    virtual ~Option(); // Virtual destructor
    Option& operator=(const Option& source);// Assignment operator

    /*void cloneParams(double S, double K, double r, double T, double sigma, double b) const;*/

// Getters and setters
    // Getters
    virtual double getS() const;
    virtual double getK() const;
    virtual double getR() const;
    virtual double getT() const;
    virtual double getSigma() const;
    virtual double getB() const;
    virtual int getOptionType() const;

    // Setters
    virtual void setS(double S);
    virtual void setK(double K);
    virtual void setR(double r);
    virtual void setT(double T);
    virtual void setSigma(double sigma);
    virtual void setB(double b);
    virtual void setOptionType(int option_type);

// Will be overloaded later
    double Price() const; // Option pricing method

// Switch between calls and puts
    void toggle ();

// To access option variables in pricing methods
friend class BSPricer;

};


#endif