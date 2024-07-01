cmake_minimum_required(VERSION 3.20)
project(HelloWorld)
set(CMAKE_CXX_STANDARD 20) # Use C++17 or your preferred standard
# Add include directories
include_directories(/usr/local/opt/boost/include)
# Define the source files
set(SOURCES
AmericanOption.cpp
MatrixPricer.cpp
BSPricer.cpp
EuropeanOption.cpp
Option.cpp
TestProgram.cpp
)
# Set the output directory for the executable to be the same as CMakeLists.txt
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

# Create the executable
add_executable(HelloWorld ${SOURCES})