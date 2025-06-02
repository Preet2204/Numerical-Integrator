#include <cstdio>
#include <iostream>
#include <cmath>
#include <functional>
#include <iomanip>
using namespace std;

float Trapezoidal(float lower_limit, float upper_limit, int intervals, float h, function<float(float)> func) {

    float sum = func(lower_limit) / 2 + func(upper_limit) / 2;
    for(int i = 1; i < intervals; ++i) {
        sum += func(lower_limit + i*h);
    }
    
    float integral = h * sum;
    return integral;
}

float Simpson13(float lower_limit, float upper_limit, int intervals, float h, function<float(float)> func) {

    float sum = func(lower_limit) + func(upper_limit);
    for(int i = 1; i < intervals; i += 2) {
        sum += 4 * func(lower_limit + i * h);
    }

    for(int i = 2; i < intervals; i += 2) {
        sum += 2 * func(lower_limit + i * h);
    }

    float integral = (h * sum) / 3;

    return integral;
}

float Simpson38(float lower_limit, float upper_limit, int intervals, float h, function<float(float)> func) {

    float sum = func(lower_limit) + func(upper_limit);
    for(int i = 1; i < intervals; i += 3) {
        sum += 3 * func(lower_limit + i * h);
        if(i + 1 < intervals) 
            sum += 3 * func(lower_limit + (i + 1) * h);
    }
    
    for(int i = 3; i < intervals; i += 3) {
        sum += 2 * func(lower_limit + i * h);
    }
    
    float integral = 3 * h * sum / 8;
    
    return integral;
}

int main() {
    
    string funcStr1 = "x^2 + 3x + 2";
    auto func1 = [](float x) -> float { return x*x + 3*x + 2; };
    auto func1integral = [](float x) -> float { return (x*x*x/3 + 3*x*x/2 + 2*x); };

    string funcStr2 = "sin(5x)/2 + 1";
    auto func2 = [](float x) -> float { return sin(5 * x) / 2 + 1; };
    auto func2integral = [](float x) -> float { return (-cos(5 * x) / 10 + x); };

    string funcStr3 = "3cos(2x) + 2";
    auto func3 = [](float x) -> float { return 3 * cos(2 * x) + 2; };
    auto func3integral = [](float x) -> float { return (3 * sin(2 * x) / 2 + 2 * x); };

    string funcStr4 = "2e^(3x)";
    auto func4 = [](float x) -> float { return 2 * exp(3 * x); };
    auto func4integral = [](float x) -> float { return 2 * exp(3 * x) / 3; };
    
    cout << "\nWelcome to the Numerical Integrator!\n\n";
    while(true) {
        cout << "------------------------------------------------------------------\n";
        cout << "Choose the function you would Like to Integrate. (Enter Number)\n";
        cout << "1. x^2 + 3*x + 2\n";
        cout << "2. sin(5*x)/2 + 1\n";
        cout << "3. 3 * cos(2*x) + 2\n";
        cout << "4. 2 * e^(3*x)\n";
        cout << "5. Exit\n";
        
        int funcChoice;
        cin >> funcChoice;
        
        while(funcChoice < 1 || funcChoice > 5) {
            cout << "Invalid choice. Please enter a valid number.\n";
            cin >> funcChoice;
        }
        if(funcChoice == 5) {
            cout << "Exiting...\n";
            return 0;
        }
        
        string funcStr;
        function<float(float)> func;
        function<float(float)> funcintegral;
        
        switch(funcChoice) {
            case 1:
                funcStr = funcStr1;
                func = func1;
                funcintegral = func1integral;
                break;
            case 2:
                funcStr = funcStr2;
                func = func2;
                funcintegral = func2integral;
                break;
            case 3:
                funcStr = funcStr3;
                func = func3;
                funcintegral = func3integral;
                break;
            case 4:
                funcStr = funcStr4;
                func = func4;
                funcintegral = func4integral;
                break;
        }

        cout << "\nEnter the lower limit of integration: ";
        float lower_limit;
        cin >> lower_limit;
        
        cout << "Enter the upper limit of Integration: ";
        float upper_limit;
        cin >> upper_limit;
        
        while(lower_limit > upper_limit) {
            cout << "Lower Limit can't be greater than Upper Limit. (Try Again)\n\n";
            cout << "Enter the lower limit of Integration: ";
            cin >> lower_limit;
            cout << "Enter the upper limit of Integration: ";
            cin >> upper_limit;
        }
        
        cout << '\n';
        cout << "For Simpson's 1/3 rule intervals Should be multiple of 2.\n";
        cout << "For Simpson's 3/8 rule intervals Should be multiple of 3.\n";
        cout << "Enter the number of intervals ";
        
        int intervals;
        cin >> intervals;
        while(intervals <= 0) {
            cout << "Intervals should be greater than 0. Enter Intervals Again: ";
            cin >> intervals;
        }
        
        float h = {(upper_limit - lower_limit) / intervals};
        
        cout << '\n';
        
        int col1 = 15, col2 = 25, col3 = 25, col4 = 25;
        float integral[3];
        float actualIntegral = funcintegral(upper_limit) - funcintegral(lower_limit);
        float error[3];
        float minError;
        
        cout << "Function: " << funcStr << '\n';;
        
        // Printing Header
        cout << left << setw(col1) << " " << setw(col2) << "Trapezoidal" << setw(col3) << "Simpson's 1/3" << setw(col4) << "Simpson's 3/8" << '\n';
        
        // Printinf 1st Row
        integral[0] = Trapezoidal(lower_limit, upper_limit, intervals, h, func);
        error[0] = abs(integral[0] - actualIntegral);
        minError = error[0];
        cout << left << setw(col1) << "Integral";
        cout << left << setw(col2) << fixed << setprecision(6) << integral[0];
        
        if(intervals % 2 == 0) {
            integral[1] = Simpson13(lower_limit, upper_limit, intervals, h, func);
            error[1] = abs(integral[1] - actualIntegral);
            minError = min(minError, error[1]);
            cout << left << setw(col3) << fixed << setprecision(6) << integral[1];
        }else {
            cout << left << setw(col3) << "Invalid Intervals!";
        }

        if(intervals % 3 == 0) {
            integral[2] = Simpson38(lower_limit, upper_limit, intervals, h, func);
            error[2] = abs(integral[2] - actualIntegral);
            minError = min(minError, error[2]);
            cout << left << setw(col4) << fixed << setprecision(6) << integral[2];
        }else {
            cout << left << setw(col4) << "Invalid Intervals!";
        }
        
        cout << '\n';
        // Printing 2nd Row
        cout << left << setw(col1) << "Error";
        cout << left << setw(col2) << fixed << setprecision(12) << error[0];
        
        if(intervals % 2 == 0) {
            cout << left << setw(col3) << fixed << setprecision(12) << error[1];
        }else {
            cout << left << setw(col3) << "Invalid Intervals!";
        }
        
        if(intervals % 3 == 0) {
            cout << left << setw(col4) << fixed << setprecision(12) << error[2];
        }else {
            cout << left << setw(col4) << "Invalid Intervals!";
        }
        
        cout << '\n';
        
        if(minError == error[0]) {
            cout << "Most Accurate Method: Trapezoidal\n";
        }
        
        if(intervals % 2 == 0 && minError == error[1]) {
            cout << "Most Accurate Method: Simpson's 1/3 Rule\n";
        }
        
        if(intervals % 3 == 0 && minError == error[2]) {
            cout << "Most Accurate Method: Simpson's 3/8 Rule\n";
        }
        
        cout << "\n";
    }
}
