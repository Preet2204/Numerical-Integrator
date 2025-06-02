# Numerical Integration Solver

**Author**: Siddhapura Preet Kumar  
**Date**: June 2, 2025  
**Language**: C++

## 1. Introduction
This project implements a numerical integration solver in C++ to compute the definite integral of a function using three methods: the Trapezoidal Rule, Simpson’s 1/3 Rule, and Simpson’s 3/8 Rule. I developed this project to enhance my understanding of numerical methods, which are fundamental to my interest in Applied Mathematics, and to improve my C++ programming skills as part of my preparation for a master’s program and a summer 2026 research internship.

## 2. Problem Statement
The objective is to calculate the definite integral $ \int_a^b f(x) \, dx $ for a given function \( f(x) \) over an interval \([a, b]\) using numerical methods. The program supports four predefined functions and compares the numerical results with the exact integral to compute errors, providing insights into the accuracy of each method.

## 3. Approach and Methodology
The project uses three numerical integration methods:

- **Trapezoidal Rule**: Approximates the integral as:
  \[
  \int_a^b f(x) \, dx \approx \frac{h}{2} \left( f(a) + 2\sum_{i=1}^{n-1} f(x_i) + f(b) \right),
  \]
  where \( h = \frac{b-a}{n} \), and \( n \) is the number of subintervals.
- **Simpson’s 1/3 Rule**: Approximates the integral as:
  \[
  \int_a^b f(x) \, dx \approx \frac{h}{3} \left( f(a) + 4\sum_{i=1,3,\dots}^{n-1} f(x_i) + 2\sum_{i=2,4,\dots}^{n-2} f(x_i) + f(b) \right),
  \]
  requiring \( n \) to be even.
- **Simpson’s 3/8 Rule**: Approximates the integral as:
  \[
  \int_a^b f(x) \, dx \approx \frac{3h}{8} \left( f(a) + 3\sum_{i=1,4,\dots}^{n-2} f(x_i) + 3\sum_{i=2,5,\dots}^{n-1} f(x_i) + 2\sum_{i=3,6,\dots}^{n-3} f(x_i) + f(b) \right),
  \]
  requiring \( n \) to be a multiple of 3.

I implemented these methods in C++ by:
1. Allowing the user to select from four predefined functions.
2. Taking user inputs for the interval \([a, b]\) and the number of subintervals \( n \).
3. Computing the integral using all applicable methods and comparing with the exact value to calculate errors.

## 4. Implementation Details
The project is written in C++ and uses the following features:
- **Function Selection**: Utilizes `std::function` and lambda functions to dynamically select from four predefined functions: \( x^2 + 3x + 2 \), \( \sin(5x)/2 + 1 \), \( 3\cos(2x) + 2 \), and \( 2e^{3x} \).
- **Input Validation**: Ensures valid inputs for the interval (\( a < b \)), number of subintervals (\( n > 0 \)), and method-specific requirements (e.g., \( n \) even for Simpson’s 1/3 Rule).
- **Output Formatting**: Displays results in a table format using `setw` and `setprecision` for readability, showing the integral and error for each method.

## 5. Results
I tested the program with the following cases:
- **Function**: \( x^2 + 3x + 2 \), Interval: \([0, 2]\), \( n = 12 \)
  - Exact Integral: \( \frac{38}{3} \approx 12.666667 \)
  - Trapezoidal: 12.675926, Error: 0.009259223938
  - Simpson’s 1/3: 12.666667, Error: 0.000000000000
  - Simpson’s 3/8: 12.666667, Error: 0.000000
- **Function**: \( \sin(5x)/2 + 1 \), Interval: \([0, \pi]\), \( n = 30 \)
  - Exact Integral: \( \pi \approx 3.141593 \)
  - Trapezoidal: 3.337002, Error: 0.004590511322
  - Simpson’s 1/3: 3.341680, Error: 0.000086784363
  - Simpson’s 3/8: 3.341794, Error: 0.000201225281
- **Function**: \( 2e^{3x} \), Interval: \([0, 1]\), \( n = 100 \)
  - Exact Integral: \( \frac{2(e^3 - 1)}{3} \approx 13.365037 \)
  - Trapezoidal: 12.724645, Error: 0.000953674316
  - Simpson’s 1/3: 12.723693, Error: 0.000001907349
  - Simpson’s 3/8: Invalid Intervals!

## 6. Challenges and Learnings
I faced challenges in calculating the exact integrals for trigonometric functions and formatting the output table to align properly. I learned to use `std::function` for dynamic function selection, improved my input validation skills, and gained a deeper understanding of numerical integration methods and their accuracy through error analysis.

## 7. Future Improvements
Future enhancements could include:
- Adding numerical stability checks for large intervals or high numbers of subintervals.
- Supporting user-defined functions through parsing.
- Implementing additional numerical methods, such as Gaussian Quadrature.

## 8. References
- “Numerical Methods for Engineers” by Chapra and Canale (for numerical integration formulas).
- GeeksforGeeks (C++ tutorials on input/output and formatting).
- C++ Reference (for `std::function` and lambda functions).
