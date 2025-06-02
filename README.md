# Numerical Integration Solver

**Author**: Siddhapura Preet Kumar  
**Date**: June 2, 2025  
**Language**: C++

## 1. Introduction
This project implements a numerical integration solver in C++ to compute the definite integral of a function using three methods: the Trapezoidal Rule, Simpson’s 1/3 Rule, and Simpson’s 3/8 Rule. I developed this project to enhance my understanding of numerical methods—fundamental to my interest in Applied Mathematics—and to improve my C++ programming skills as part of my preparation for a master’s program and a summer 2026 research internship.

## 2. Problem Statement
The objective is to calculate the definite integral  
![∫_a^b f(x) dx](https://latex.codecogs.com/png.image?\dpi{120}\int_a^b%20f(x)\,dx)  
for a given function f(x) over the interval [a, b] using numerical methods. The program supports four predefined functions and compares each numerical result with its exact integral to compute errors, providing insights into the accuracy of each method.

## 3. Approach and Methodology
The project uses three classical numerical integration methods:

- **Trapezoidal Rule**  
  Approximates the integral as:  

  ![Trapezoidal formula](https://latex.codecogs.com/png.image?\dpi{120}\int_a^b%20f(x)\,dx\approx\frac{h}{2}\bigl(f(a)+2\sum_{i=1}^{n-1}f(x_i)+f(b)\bigr))  

  where  
  ![h formula](https://latex.codecogs.com/png.image?\dpi{100}h=\frac{b-a}{n})  
  and n is the number of subintervals.

- **Simpson’s 1/3 Rule**  
  Approximates the integral as:  

  ![Simpson 1/3 formula](https://latex.codecogs.com/png.image?\dpi{120}\int_a^b%20f(x)\,dx\approx\frac{h}{3}\Bigl(f(a)+4\sum_{\substack{i=1\\i\,\text{odd}}}^{n-1}f(x_i)+2\sum_{\substack{i=2\\i\,\text{even}}}^{n-2}f(x_i)+f(b)\Bigr))  

  requiring n to be even.

- **Simpson’s 3/8 Rule**  
  Approximates the integral as:  

  ![Simpson 3/8 formula](https://latex.codecogs.com/png.image?\dpi{120}\int_a^b%20f(x)\,dx\approx\frac{3h}{8}\Bigl(f(a)+3\sum_{\substack{i=1\\i\equiv1\pmod3}}^{n-2}f(x_i)+3\sum_{\substack{i=2\\i\equiv2\pmod3}}^{n-1}f(x_i)+2\sum_{\substack{i=3\\i\equiv0\pmod3}}^{n-3}f(x_i)+f(b)\Bigr))  

  requiring n to be a multiple of 3.

**Implementation Outline:**  
1. Allow the user to select one of four predefined functions.  
2. Prompt for interval endpoints a and b, plus the number of subintervals n.  
3. Compute the integral using all applicable methods (checking that n is even for 1/3 Rule, multiple of 3 for 3/8 Rule).  
4. Compare each numerical result with the exact integral and display the absolute error.

## 4. Implementation Details
- **Function Selection**  
  Uses `std::function<double(double)>` and lambda expressions to switch among four predefined functions:  
  1. \(x^2 + 3x + 2\)  
  2. \(sin(5x)/2 + 1\)  
  3. \(3cos(2x) + 2\)  
  4. \(2e^{3x}\)

- **Input Validation**  
  - Checks that \(a < b\).  
  - Ensures \(n > 0\).  
  - Verifies that \(n\) is even when using Simpson’s 1/3 Rule.  
  - Verifies that \(n\) is a multiple of 3 when using Simpson’s 3/8 Rule.

- **Output Formatting**  
  Uses `std::setw` and `std::setprecision` to produce a neatly aligned table. Numeric values are shown with six decimal places for clarity.

## 5. Results
Test cases (all values rounded to six decimals in the output):

1. **Function**: \(x^2 + 3x + 2\)  
   **Interval**: \([0, 2]\), \(n = 12\)  
   - Exact Integral: \(38/3 = 12.666667\)  
   - Trapezoidal: 12.675926  (Error: 0.009259)  
   - Simpson’s 1/3: 12.666667  (Error: 0.000000)  
   - Simpson’s 3/8:  12.666667  (Error: 0.000000)

2. **Function**: \(sin(5x)/2 + 1\)  
   **Interval**: \([0, 3.141592]\), \(n = 30\)  
   - Trapezoidal: 3.337002  (Error: 0.004591)  
   - Simpson’s 1/3: 3.341680  (Error: 0.000087)  
   - Simpson’s 3/8:  3.341794  (Error: 0.000201)

3. **Function**: \(2 e^{3x}\)  
   **Interval**: \([0, 1]\), \(n = 100\)  
   - Trapezoidal: 12.724645  (Error: 0.640392)  
   - Simpson’s 1/3: 12.723693  (Error: 0.641344)  
   - Simpson’s 3/8:  Invalid (n = 100 is not a multiple of 3)

> **Note:** For Simpson’s 3/8 Rule, \(n\) must be a multiple of 3. Because 100 ÷ 3 is not integral, the solver reports “Invalid” for that method.

## 6. Challenges and Learnings
- Deriving the exact integrals of trigonometric expressions required care (e.g., integrating \(\tfrac12\sin(5x)\)).  
- Formatting the console‐output table with `std::setw` and `std::setprecision` to align decimal points took some trial-and-error.  
- I gained confidence using `std::function` and lambdas to switch functions at runtime, and I deepened my understanding of error behavior in numerical quadrature.

## 7. Future Improvements
- Add numerical‐stability checks for very large intervals or extremely fine subintervals.  
- Allow the user to input a custom function (e.g., via a simple expression parser).  
- Implement higher-order or specialized methods (e.g., Gaussian Quadrature, adaptive quadrature).

## 8. References
- Chapra, S. C. & Canale, R. P. **Numerical Methods for Engineers** (for theory of numerical integration).  
- GeeksforGeeks – tutorials on C++ I/O and formatting (e.g., `setw`, `setprecision`).  
- cppreference.com – documentation for `std::function`, lambdas, and I/O manipulators.

