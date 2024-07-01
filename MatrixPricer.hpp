// MatrixPricer.hpp
// Level 9 Group A
// 
// MatrixPricer class for mesher
// Single Responsibility: To create an encapsulated matrix (and vector) for outputting batch test results
// Methods implemented: 
//
// @file MatrixPricer.hpp
// @author Mark Bogorad
// @version 1.0
//

#ifndef MATRIXPRICER_HPP 
#define MATRIXPRICER_HPP

#include <vector> // library for using vector
// Define a template Matrix class for simplicity in this example
class MatrixPricer {
private:
    double begin; // Start of range
    double end; // End of range
    double h; // Step size
    
public:
// Canonical header:
    MatrixPricer(); // Default constructor
    MatrixPricer(const MatrixPricer& other); // Copy constructor
    MatrixPricer(double begin, double end, double h); // Parameterized constructor
    ~MatrixPricer();
    MatrixPricer& operator=(const MatrixPricer& source);// Assignment operator

// Vector of doubles function
    std::vector<double> GenerateMesh() const; // This will be a row in mesher
// Mesher (matrix)
    std::vector<std::vector<double>> OptionMatrix(int parameterToVary, const std::vector<double>& defaultParams) const; // Pricing matrix where each row is a vector of doubles

};

#endif





/*
template<typename T>
class MatrixPricer {
private:
    std::vector<std::vector<T>> data;
    size_t rows, cols;

public:
    MatrixPricer(size_t rows, size_t cols, T initial)
        : rows(rows), cols(cols), data(rows, std::vector<T>(cols, initial)) {}

    // Accessor to set a value
    void set(size_t row, size_t col, T value) {
        data[row][col] = value;
    }

    // Accessor to get a value
    T get(size_t row, size_t col) const {
        return data[row][col];
    }

    size_t getRows() const { return rows; }
    size_t getCols() const { return cols; }
};
*/