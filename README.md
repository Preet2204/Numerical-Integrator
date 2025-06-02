# Numerical Integration Solver

**Author**: Siddhapura Preet Kuman  
**Date**: June 2, 2025  
**Language**: C++

## 1. Introduction
This project implements a numerical integration solver in C++ to compute the definite integral of a function using three methods: the Trapezoidal Rule, Simpson’s 1/3 Rule, and Simpson’s 3/8 Rule. I developed this project to deepen my understanding of numerical methods, which are fundamental to my interest in Applied Mathematics, and to enhance my C++ programming skills. The solver calculates integrals, compares them with exact values to determine errors, and identifies the most accurate method for each computation.

## 2. Problem Statement
The objective is to calculate the definite integral  
![∫_a^b f(x) dx](https://latex.codecogs.com/png.image?\dpi{120}\int_a^b%20f(x)\,dx)  
for a given function \( f(x) \) over an interval \([a, b]\) using numerical methods. The program supports four predefined functions, computes the integral using all applicable methods, compares numerical results with the exact integral to calculate errors, and identifies the method with the smallest error, providing insights into the accuracy of each approach.

## 3. Approach and Methodology
The project employs three numerical integration methods:

- **Trapezoidal Rule**  
  Approximates the integral as:  
  ![Trapezoidal formula](https://latex.codecogs.com/png.image?\dpi{150}\int_a^b%20f(x)\,dx\approx\frac{h}{2}\bigl(f(a)+2\sum_{i=1}^{n-1}f(x_i)+f(b)\bigr))  
  where  
  ![h formula](https://latex.codecogs.com/png.image?\dpi{100}h=\frac{b-a}{n})  
  and \( n \) is the number of subintervals.

- **Simpson’s 1/3 Rule**  
  Approximates the integral as:  
  ![Simpson 1/3 formula](https://latex.codecogs.com/png.image?\dpi{150}\int_a^b%20f(x)\,dx\approx\frac{h}{3}\Bigl(f(a)+4\sum_{\substack{i=1\i\equiv1\pmod2}}^{n-1}f(x_i)+2\sum_{\substack{i=2\\i\equiv0\pmod2}}^{n-2}f(x_i)+f(b)\Bigr))  
  requiring \( n \) to be even.

- **Simpson’s 3/8 Rule**  
  Approximates the integral as:  
  ![Simpson 3/8 formula](https://latex.codecogs.com/png.image?\dpi{150}\int_a^b%20f(x)\,dx\approx\frac{3h}{8}\Bigl(f(a)+3\sum_{\substack{i=1\\i\equiv1\pmod3}}^{n-2}f(x_i)+3\sum_{\substack{i=2\\i\equiv2\pmod3}}^{n-1}f(x_i)+2\sum_{\substack{i=3\\i\equiv0\pmod3}}^{n-3}f(x_i)+f(b)\Bigr))  
  requiring \( n \) to be a multiple of 3.

**Implementation Outline:**  
1. Allow the user to select one of four predefined functions.  
2. Prompt for interval endpoints \( a \) and \( b \), plus the number of subintervals \( n \).  
3. Compute the integral using all applicable methods (checking that \( n \) is even for Simpson’s 1/3 Rule, a multiple of 3 for Simpson’s 3/8 Rule).  
4. Compare each numerical result with the exact integral to calculate absolute errors.  
5. Identify the method with the smallest error and display it as the most accurate method.

## 4. Implementation Details
- **Function Selection**  
  Uses `std::function<float(float)>` and lambda expressions to switch among four predefined functions:  
  1. \( x^2 + 3x + 2 \)  
  2. \( \sin(5x)/2 + 1 \)  
  3. \( 3\cos(2x) + 2 \)  
  4. \( 2e^{3x} \)

- **Input Validation**  
  - Ensures \( a < b \).  
  - Validates that \( n > 0 \).  
  - Verifies that \( n \) is even when using Simpson’s 1/3 Rule.  
  - Verifies that \( n \) is a multiple of 3 when using Simpson’s 3/8 Rule.

- **Output Formatting**  
  Uses `std::setw` and `std::setprecision` to produce a neatly aligned table. Integral values are shown with six decimal places, and errors are shown with twelve decimal places for clarity. The program also displays the most accurate method based on the smallest error.

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
- Formatting the output table with `std::setw` and `std::setprecision` to align decimal points took some trial-and-error.
- I gained confidence in using `std::function` and lambda expressions for dynamic function selection, deepened my understanding of numerical errors, and improved my ability to compare the accuracy of numerical methods.

## 7. Future Improvements
- Add numerical stability checks for very large intervals or extremely high numbers of subintervals.
- Allow the user to input custom functions via a simple expression parser.
- Implement additional methods, such as Gaussian Quadrature or adaptive quadrature, for higher accuracy.

## 8. Potential Research Applications
This numerical integration solver can be applied in computational research, particularly in physics and engineering. For example:
- In computational physics, it can calculate the work done by a force field over a path by integrating the force function.
- In numerical simulations, it can compute areas under curves representing physical quantities (e.g., velocity-time graphs to find displacement).
This project demonstrates my ability to implement and analyze numerical methods, preparing me for research tasks in a summer 2026 internship.

## 9. References
- GeeksforGeeks – tutorials on C++ I/O and formatting (e.g., `setw`, `setprecision`).