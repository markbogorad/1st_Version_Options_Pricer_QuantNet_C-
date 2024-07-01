#include "Option.hpp"
#include "EuropeanOption.hpp"
#include "BSPricer.hpp"
#include "MatrixPricer.hpp"
#include "AmericanOption.hpp"
#include <iostream>
#include <vector>

#include <boost/exception/all.hpp>

using namespace std;
BSPricer bspricer; // Creating an instance of the BSPricer class for parameter check, don't need to change/redefine this for each batch. Tested by inputting 1.12 for r in random batches (should be out of bounds)

int main() {
    cout << "\nGROUP A: EUROPEAN OPTIONS " << endl;
    cout << "\n\nParts A & B: Batch testing to get price of calls/puts and pricing using put-call parity" << endl;
    cout << "\n____________________________________Batch 1____________________________________" << endl; 
    // Declare and initialize variables
    double S = 108, K = 120, r = 0.045, T = 1.45, sigma = 0.51, b = 0; // Batch 1 variables 
    int option_type = 1; // Call option

    try {
        bspricer.checkParameters (S, K, r, T, sigma, b); // Parameter check function (detials in BSPricer)
        // Proceed with calculations if all checks pass
        EuropeanOption Batch1(S, K, r, T, sigma, b, option_type); // Create an instance of the EuropeanOption class
        cout << "S: " << S << ", K: " << K << ", r: " << r << ", T: " << T << ", sigma: " << sigma << ", b: " << b << endl; 
        cout << "Using Black-Scholes:" << endl; 

    // Black-Scholes Pricing
        // Call:
        double BSPrice = Batch1.Price(); // Call price (from option type = 1)
        double c = Batch1.Price(); // Saving call price in variable called c for direct output and to use in PCP_Check
        cout << "\tCall price: " << c << endl;
        // Put:
        Batch1.toggle(); // Toggle to put
        double p = Batch1.Price(); // Saving put price in variable called p for direct output
        cout << "\tPut price: " << Batch1.Price() << endl;

    //Put-Call Parity pricing (given one (p or c) find the other)
        Batch1.toggle(); // Toggle back to call
        cout << "Using Put-Call Parity:" << endl;
        // Call:
        double PCPPrice = Batch1.PCP_Price(); // Will start with call as the last input is the put from BS
        cout << "\tCall price from put (PCP): " << Batch1.PCP_Price() << endl;
        // Put:
        Batch1.toggle(); // Toggle to put
        cout << "\tPut price from call (PCP): " << Batch1.PCP_Price() << endl;
    // Ensure PCP holds
        cout << "PCP Check via BSPricer: " << endl;
        bool PCPCheck = bspricer.PCP_Check(S, K, r, T, c, p); // C and P inserted here from previous calculations. Result of check is encapsulated in PCP_Check, which is in BSPricer
    // If parameters check failed, catch here:
    } catch (const std::exception& e) { 
            std::cerr << "Parameter check failed: " << e.what() << std::endl;
    }

    // The rest of these batches repeat the same pattern as Batch1:
    cout << "\n\n____________________________________Batch 2____________________________________" << endl;
    S = 100, K = 100, r = 0.0, T = 1.0, sigma = 0.2, b = r;
    option_type = 1;

    try {
        bspricer.checkParameters (S, K, r, T, sigma, b);

        EuropeanOption Batch2(S, K, r, T, sigma, b, option_type);
        cout << "S: " << S << ", K: " << K << ", r: " << r << ", T: " << T << ", sigma: " << sigma << ", b: " << b << endl;
        cout << "Using Black-Scholes:" << endl;

    // Black-Scholes Pricing
        double BSPrice = Batch2.Price();
        double c = Batch2.Price();
        cout << "\tCall price: " << c << endl;
        Batch2.toggle(); // Toggle to put
        double p = Batch2.Price();
        cout << "\tPut price: " << Batch2.Price() << endl;

    //Put-Call Parity pricing (given one (p or c) find the other)
        Batch2.toggle(); // Toggle back to call
        cout << "Using Put-Call Parity:" << endl;
        double PCPPrice = Batch2.PCP_Price(); // Will start with call as the last input is the put from BS
        cout << "\tCall price from put (PCP): " << Batch2.PCP_Price() << endl;
        Batch2.toggle(); // Toggle to put
        cout << "\tPut price from call (PCP): " << Batch2.PCP_Price() << endl;

    // Ensure PCP holds
        cout << "PCP Check via BSPricer: " << endl;
        bool PCPCheck = bspricer.PCP_Check(S, K, r, T, c, p);

    // Catch exception
    } catch (const std::exception& e) {
            std::cerr << "Parameter check failed: " << e.what() << std::endl;
            // Handle the error (e.g., by not proceeding with further calculations)
    }

    cout << "\n\n____________________________________Batch 3____________________________________" << endl;
    S = 5, K = 10, r = 0.12, T = 1.0, sigma = 0.50, b = r;
    option_type = 1;

    try {
        bspricer.checkParameters (S, K, r, T, sigma, b);
        
        EuropeanOption Batch3(S, K, r, T, sigma, b, option_type);
        cout << "S: " << S << ", K: " << K << ", r: " << r << ", T: " << T << ", sigma: " << sigma << ", b: " << b << endl;
        cout << "Using Black-Scholes:" << endl;

    // Black-Scholes Pricing
        double BSPrice = Batch3.Price();
        double c = Batch3.Price();
        cout << "\tCall price: " << c << endl;
        Batch3.toggle(); // Toggle to put
        double p = Batch3.Price();
        cout << "\tPut price: " << Batch3.Price() << endl;

    //Put-Call Parity pricing (given one (p or c) find the other)
        Batch3.toggle(); // Toggle back to call
        cout << "Using Put-Call Parity:" << endl;
        double PCPPrice = Batch3.PCP_Price(); // Will start with call as the last input is the put from BS
        cout << "\tCall price from put (PCP): " << Batch3.PCP_Price() << endl;
        Batch3.toggle(); // Toggle to put
        cout << "\tPut price from call (PCP): " << Batch3.PCP_Price() << endl;

    // Ensure PCP holds
       cout << "PCP Check via BSPricer: " << endl;
        bool PCPCheck = bspricer.PCP_Check(S, K, r, T, c, p);

    // Catch exception
    } catch (const std::exception& e) {
            std::cerr << "Parameter check failed: " << e.what() << std::endl;
            // Handle the error (e.g., by not proceeding with further calculations)
    }

    cout << "\n\n____________________________________Batch 4____________________________________" << endl;
    S = 100, K = 100, r = 0.08, T = 30.0, sigma = 0.30, b = r;
    option_type = 1;

    try {
        bspricer.checkParameters (S, K, r, T, sigma, b);
     
        EuropeanOption Batch4(S, K, r, T, sigma, b, option_type);
        cout << "S: " << S << ", K: " << K << ", r: " << r << ", T: " << T << ", sigma: " << sigma << ", b: " << b << endl;
        cout << "Using Black-Scholes:" << endl;

    // Black-Scholes Pricing
        double BSPrice = Batch4.Price();
        double c = Batch4.Price();
        cout << "\tCall price: " << c << endl;
        Batch4.toggle(); // Toggle to put
        double p = Batch4.Price();
        cout << "\tPut price: " << Batch4.Price() << endl;

    //Put-Call Parity pricing (given one (p or c) find the other)
        Batch4.toggle(); // Toggle back to call
        cout << "Using Put-Call Parity:" << endl;
        double PCPPrice = Batch4.PCP_Price(); // Will start with call as the last input is the put from BS
        cout << "\tCall price from put (PCP): " << Batch4.PCP_Price() << endl;
        Batch4.toggle(); // Toggle to put
        cout << "\tPut price from call (PCP): " << Batch4.PCP_Price() << endl;

    // Ensure PCP holds
        cout << "PCP Check via BSPricer: " << endl;
        bool PCPCheck = bspricer.PCP_Check(S, K, r, T, c, p);
        Batch4.toggle(); // toggle back to call for future

    // Catch exception
    } catch (const std::exception& e) {
            std::cerr << "Parameter check failed: " << e.what() << std::endl;
    }


    cout << "\n\nPart C: Monotonically increasing underlying values (S)" << endl;
    cout << "________________________________________________________________________" << endl;
    S=60, K = 65, r = 0.08, T = 0.25, sigma = 0.30, b = r; // Batch 1 data for simplicity
    EuropeanOption Batch1(S, K, r, T, sigma, b, option_type); // Re-instantiating Batch1
    MatrixPricer vectorsPricer (60, 70, 1); // MatrixPricer object for making a vector of prices

    auto S_values = vectorsPricer.GenerateMesh(); // Auto used for simplicity instead of std::vector<double>
    
    std::vector<double> CallPrices, PutPrices; // Vectors to hold call and put prices

    // Calculate Call Prices
    for (double S : S_values) {
        Batch1.setS(S); // To update S (all getters/setters implemented if one were to make this a different variable for the vector)
        // Calls
        Batch1.setOptionType(1); // 1 for call
        double callPrice = Batch1.Price(); // double callPrice to hold the calculated price
        CallPrices.push_back(callPrice); // Push back call price into vector
        // No need for toggle, option type set directly via setOptionType
        // Puts
        Batch1.setOptionType(2); // 2 for put
        double putPrice = Batch1.Price(); // double putPrice to hold the calculated price
        PutPrices.push_back(putPrice); // Push back put price into vector
    }

    // Output Call Prices
    cout << "\nCall Prices:" << endl;
    for (size_t i = 0; i < S_values.size(); ++i) { // size_t used for simplicity
        cout << "\tPrice for S=" << S_values[i] << ": " << CallPrices[i] << endl;
    }

    // Output Put Prices
    cout << "\nPut Prices:" << endl;
    for (size_t i = 0; i < S_values.size(); ++i) {
        cout << "\tPrice for S=" << S_values[i] << ": " << PutPrices[i] << endl;
    }



    cout << "\n\nPart D: Monotonically increasing matrix with desired input: " << endl;
    cout << "________________________________________________________________________" << endl;
    std::vector<double> defaultParams = {60, 65, 0.08, 0.25, 0.30, 0.08}; // Batch1 values (S, K ,r T, sigma, b)
    MatrixPricer matrixPricer(50, 70, 1); 
 
    int parameterToVary = 1; // Varying parameter ([0 = S] [1 = K] [2 = r] [3 = T] [4 = sigma] [5=b])

    // Generate the parameter matrix
    auto paramMatrix = matrixPricer.OptionMatrix(parameterToVary, defaultParams);

    // Iterate over each parameter set and calculate option prices
    for (const auto& params : paramMatrix) {
        // Parameter order: S, K, r, T, sigma, b
        BSPricer bsPricer(params[0], params[1], params[2], params[3], params[4], params[5], 1); // '1' for call option type
        
        double callPrice = bsPricer.CallPrice(params[0], params[1], params[2], params[3], params[4], params[5], 1);
        double putPrice = bsPricer.PutPrice(params[0], params[1], params[2], params[3], params[4], params[5], 2);

        cout << fixed << setprecision(2);
        cout << "S: " << params[0] << ", K: " << params[1] << ", r: " << params[2] << ", T: " << params[3] << ", sigma: " << params[4] << ", b: " << params[5] <<
        setprecision(5) << " | Call Price: " << callPrice << ", Put Price: " << putPrice << endl;
    }



    cout << "\n\nGreeks Part A: Calculating gamma for call and put: " << endl;
    cout << "________________________________________________________________________\n" << endl;
    S = 108, K = 120, r = 0.045, T = 1.45, sigma = 0.51, b = 0;
    option_type = -1;
    try {
        double callDelta = bspricer.CallDelta(S, K, r, T, sigma, b);
        double putDelta = bspricer.PutDelta(S, K, r, T, sigma, b);
        double gamma = bspricer.Gamma(S, K, r, T, sigma, b); // or bspricer.PutGamma(), should yield the same value

        cout << "Call Delta: " << callDelta << endl;
        cout << "Put Delta: " << putDelta << endl;
        cout << "Gamma (for both call and put): " << gamma << endl;
    
    } catch (const std::exception& e) { 
            std::cerr << "Parameter check failed: " << e.what() << std::endl;
    }



    cout << "\n\nGreeks Part B: Delta price in monotonically increasing S vector: " << endl;
    cout << "________________________________________________________________________" << endl;

    S = 105, K = 100, r = 0.1, T = 0.5, sigma = 0.36, b = 0; // Input vector 
    MatrixPricer vectorsSensitivities (100, 110, 1); // MatrixPricer object for making a vector of prices

    auto S_valuesGreeks = vectorsSensitivities.GenerateMesh(); // Auto used for simplicity instead of std::vector<double>
    
    std::vector<double> CallDeltas, PutDeltas, Gammas; // Vectors to hold call and put prices

    // Calculate Call Prices
    for (double S : S_valuesGreeks) {
        Batch1.setS(S); // To update S (all getters/setters implemented if one were to make this a different variable for the vector)
        // Calls
        Batch1.setOptionType(1); // 1 for call
        double callDelta = bspricer.CallDelta(S, K, r, T, sigma, b); // double callPrice to hold the calculated price
        CallDeltas.push_back(callDelta); // Push back call price into vector
        // No need for toggle, option type set directly via setOptionType
        // Puts
        Batch1.setOptionType(2); // 2 for put
        double putDelta = bspricer.PutDelta(S, K, r, T, sigma, b); // double putPrice to hold the calculated price
        PutDeltas.push_back(putDelta); // Push back put price into vector

        double gamma = bspricer.Gamma(S, K, r, T, sigma, b);
        Gammas.push_back(gamma);

    }

    // Output Call Deltas
    cout << "\nCall Deltas:" << endl;
    for (size_t i = 0; i < S_valuesGreeks.size(); ++i) {
        cout << "\tDelta for S=" << S_valuesGreeks[i] << ": " << CallDeltas[i] << endl;
    }

    // Output Put Deltas
    cout << "\nPut Deltas:" << endl;
    for (size_t i = 0; i < S_valuesGreeks.size(); ++i) {
        cout << "\tDelta for S=" << S_valuesGreeks[i] << ": " << PutDeltas[i] << endl;
    }

    // Output Gammas
    cout << "\nGammas:" << endl;
    for (size_t i = 0; i < S_valuesGreeks.size(); ++i) {
        cout << "\tDelta for S=" << S_valuesGreeks[i] << ": " << Gammas[i] << endl;
    }



    cout << "\n\nGreeks Part C: Input option parameter matrix, recieve matrix of delta or gamma: " << endl;
    cout << "________________________________________________________________________" << endl;

    std::vector<double> G_defaultParams = {105, 100, 0.1, 0.5, 0.36, 0}; // 
    MatrixPricer G_matrixPricer(90, 120, 1); // Assuming a range from 60 to 70 with step size of 1
    
    int G_parameterToVary = 1; // Varying parameter ([0 = S] [1 = K] [2 = r] [3 = T] [4 = sigma] [5=b])
    
    // Generate the parameter matrix
    auto G_paramMatrix = G_matrixPricer.OptionMatrix(G_parameterToVary, G_defaultParams);

    // Iterate over each parameter set and calculate option prices
    for (const auto& params : G_paramMatrix) {
        // Parameter order: S, K, r, T, sigma, b
        BSPricer bsPricer(params[0], params[1], params[2], params[3], params[4], params[5], 1); // '1' for call option type
        
        double callDelta = bsPricer.CallDelta(params[0], params[1], params[2], params[3], params[4], params[5]);
        double putDelta = bsPricer.PutDelta(params[0], params[1], params[2], params[3], params[4], params[5]);
        double Gamma = bsPricer.Gamma(params[0], params[1], params[2], params[3], params[4], params[5]);

       
        cout << fixed << setprecision(2);
        cout <<  "S: " << params[0] << ", K: " << params[1] << ", r: " << params[2] << ", T: " << params[3] << ", sigma: " << params[4] << ", b: " << params[5] <<
        setprecision(5) << " | Call Delta: " << callDelta << ", Put Delta: " << putDelta << ", Gamma: " << Gamma << endl;
        
    }

    cout << "\n\nGreeks Part D: Divided Differences: " << endl;
    cout << "________________________________________________________________________" << endl;
    BSPricer bsPricer(105, 100, 0.1, 0.5, 0.36, 0, 1); // '1' for call option type

    // Test Delta and Gamma approximations with various h values
    std::vector<double> hs = {10, 1, 0.00001}; // Different h values for sensitivity analysis: as h gets smaller, result should converge to more accurate delta/gamma
    for (auto h : hs) {
        double deltaApprox = bsPricer.DeltaApprox(h);
        double gammaApprox = bsPricer.GammaApprox(h);
         cout << "For h = " << h << ": Call Delta Approx = " << deltaApprox << ", Call Gamma Approx = " << gammaApprox << endl;
    }



    cout << "\n\nGROUP B: AMERICAN OPTIONS " << endl;
    cout << "\n\nPart A & B: Testing American Option Formulae: " << endl;
    cout << "________________________________________________________________________" << endl;

    S = 110, K = 100, r = 0.1, sigma = 0.10, b = 0.02; // Test variables
    option_type = 1; // Call option

    try {
        bspricer.checkParameters (S, K, r, T, sigma, b); // Parameter check function (detials in BSPricer)
        // Proceed with calculations if all checks pass
        AmericanOption Test(S, K, r, sigma, b, option_type); // Create an instance of the EuropeanOption class
        cout << "S: " << S << ", K: " << K << ", r: " << r << ", sigma: " << sigma << ", b: " << b << endl; 
        cout << "Using American Pricing Methods: " << endl; 

        // Call:
        double BSPrice = Test.Price(); // Call price (from option type = 1)
        double c = Test.Price(); // Saving call price in variable called c for direct output and to use in PCP_Check
        cout << "\tCall price: " << c << endl;
        // Put:
        Test.toggle(); // Toggle to put
        double p = Test.Price(); // Saving put price in variable called p for direct output
        cout << "\tPut price: " << Test.Price() << endl;
    // If parameters check failed, catch here:
    } catch (const std::exception& e) { 
            std::cerr << "Parameter check failed: " << e.what() << std::endl;
    }



    cout << "\n\nPart C: American Options in monotonically increasing S vector: " << endl;
    cout << "________________________________________________________________________" << endl;

    S = 110, K = 100, r = 0.1, sigma = 0.10, b = 0.02; // Batch 1 data for simplicity
    MatrixPricer AmericanvectorsPricer (100, 110, 1); // MatrixPricer object for making a vector of prices
    AmericanOption Test(S, K, r, sigma, b, option_type);
    auto A_S_values = AmericanvectorsPricer.GenerateMesh(); // Auto used for simplicity instead of std::vector<double>
    
    std::vector<double> AmericanCallPrices, AmericanPutPrices; // Vectors to hold call and put prices

    // Calculate Call Prices
    for (double S : A_S_values) {
        Test.setS(S); // To update S (all getters/setters implemented if one were to make this a different variable for the vector)
        // Calls
        Test.setOptionType(1); // 1 for call
        double AmericancallPrice = Test.Price(); // double callPrice to hold the calculated price
        AmericanCallPrices.push_back(AmericancallPrice); // Push back call price into vector
        // No need for toggle, option type set directly via setOptionType
        // Puts
        Test.setOptionType(2); // 2 for put
        double AmericanputPrice = Test.Price(); // double putPrice to hold the calculated price
        AmericanPutPrices.push_back(AmericanputPrice); // Push back put price into vector
    }

    // Output Call Prices
    cout << "\nCall Prices:" << endl;
    for (size_t i = 0; i < A_S_values.size(); ++i) { // size_t used for simplicity
        cout << "\tPrice for S=" << A_S_values[i] << ": " << AmericanCallPrices[i] << endl;
    }

    // Output Put Prices
    cout << "\nPut Prices:" << endl;
    for (size_t i = 0; i < A_S_values.size(); ++i) {
        cout << "\tPrice for S=" << A_S_values[i] << ": " << AmericanPutPrices[i] << endl;
    }




    cout << "\n\nPart D: American Options in monotonically increasing S vector: " << endl;
    cout << "________________________________________________________________________" << endl;
    std::vector<double> A_defaultParams = {S = 110, K = 100, r = 0.1, sigma = 0.10, b = 0.02}; // Batch1 values (S, K ,r T, sigma, b)
    MatrixPricer A_matrixPricer(90, 110, 1); // 
    
    int A_parameterToVary = 1; // Varying parameter ([0 = S] [1 = K] [2 = r] [3 = sigma] [4 = b])
    
    // Generate the parameter matrix
    auto A_paramMatrix = A_matrixPricer.OptionMatrix(A_parameterToVary, A_defaultParams);

    // Iterate over each parameter set and calculate option prices
    for (const auto& params : A_paramMatrix) {
        // Parameter order: S, K, r, sigma, b, option_type
        BSPricer bsPricer(params[0], params[1], params[2], params[3], params[4], params[5], 1); // '1' for call option type
        
        double AmericanCallPrice = bsPricer.AmericanCallPrice(params[0], params[1], params[2], params[3], params[4], 1);
        double AmericanPutPrice = bsPricer.AmericanPutPrice(params[0], params[1], params[2], params[3], params[4], 2);

        cout << fixed << setprecision(2);
        cout << "S: " << params[0] << ", K: " << params[1] << ", r: " << params[2] << ", sigma: " << params[3] << ", b: " << params[4] <<
        setprecision(5) << " | Call Price: " << AmericanCallPrice << ", Put Price: " << AmericanPutPrice << endl;
    }

    return 0;
}

