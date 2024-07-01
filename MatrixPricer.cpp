
#include <vector> //library for using vector
#include <iostream>
#include <iomanip>
#include "MatrixPricer.hpp"
#include "Option.hpp"

// Canonical header:
MatrixPricer::MatrixPricer() : begin(0.0001), end(0.0001), h(0.0001) {} // Default constructor
MatrixPricer::MatrixPricer(const MatrixPricer& other) : begin(other.begin), end(other.end), h(other.h) {} // Copy constructor
MatrixPricer::MatrixPricer(double begin, double end, double h) : begin(begin), end(end), h(h) {} // Parameterized constructor
MatrixPricer::~MatrixPricer() {} // Destructor
MatrixPricer& MatrixPricer::operator=(const MatrixPricer& source) { // Assignment operator
    if (this != &source) {
        begin = source.begin;
        end = source.end;
        h = source.h;
    }
    return *this;
}

// Vector of doubles implementation
std::vector<double> MatrixPricer::GenerateMesh() const {  
    std::vector<double> mesh; // Create a vector of doubles
    for (double i = begin; i <= end; i += h) // Iterate over the range
        mesh.push_back(i); // Add the value to the vector
    return mesh; 
}


// Matrix implementation
std::vector<std::vector<double>> MatrixPricer::OptionMatrix(int parameterToVary, const std::vector<double>& defaultParams) const { // Generate a matrix of option parameters

    std::vector<double> mesh = GenerateMesh(); // Generate mesh: range over which the paramaterToVary will vary (begin, end, h)
    std::vector<std::vector<double>> result; // Create a vector of vectors of doubles called result

    for (auto meshValue : mesh) { // Iterate over the mesh using range based loop

        std::vector<double> tempParams = defaultParams; // Copy default parameters to a temporary vector tempParams
        tempParams[parameterToVary] = meshValue; // Override the specific parameter with the mesh value
        result.push_back(tempParams); // Add the vector of doubles to the vector of vectors of doubles
    }
    return result;
}




/*
std::vector<double> Matrix(const MatrixPricer<double>& params, const Option& optionTemplate) { // Matrix would be it's own interface
        std::vector<double> results;
        for (size_t i = 0; i < params.getRows(); ++i) {
            // Order: S, K, r, T, sigma, b
            std::shared_ptr<Option> option(optionTemplate.cloneParams( // Clone params would be a copy method within option class
            params.get(i, 0), // S
            params.get(i, 1), // K
            params.get(i, 2), // r
            params.get(i, 3), // T
            params.get(i, 4), // sigma
            params.get(i, 5)  // b 
            ));
            results.push_back(option->Price());
        }
        return results;
}
*/