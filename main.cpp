#include <cstdio>
#include <iostream>
#include <cmath>
#include <functional>
using namespace std;

float Trapezoidal(float lower_limit, float upper_limit, int intervals, function<float(float)> func) {
    
    float h = (upper_limit - lower_limit) / intervals;
    
    float sum = func(lower_limit) / 2 + func(upper_limit) / 2;
    
    for(int i = 1; i < intervals; ++i) {
        sum += func(lower_limit + i*h);
    }
    
    float integral = h * sum;
    return integral;
}

float Simpson13(float lower_limit, float upper_limit, int intervals, function<float(float)> func) {
    
    float h = (upper_limit - lower_limit) / intervals;

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

float Simpson38(float lower_limit, float upper_limit, int intervals, function<float(float)> func) {
    
    float h = (upper_limit - lower_limit) / intervals;

    float sum = func(lower_limit) + func(upper_limit);
    
    for(int i = 1; i < intervals; i += 3) {
        sum += 3 * func(lower_limit + i * h);
        if(i + 1 < intervals) 
            sum += 3 * func(lower_limit + (i + 1) * h);
    }
    
    for(int i = 3; i < intervals; i += 3) {
        sum += 2 * func(lower_limit + i * h);
    }
    
    float integ = 3 * h * sum / 8;
    
    return integ;
}

int main() {
    
    auto func1 = [](float x) -> float { return x*x + 3*x + 2; };
    auto func2 = [](float x) -> float { return sin(5 * x) / 2 + 1; };
    auto func3 = [](float x) -> float { return 3 * cos(2 * x) + 1; };
    auto func4 = [](float x) -> float { return 2 * exp(3 * x); };
    
    cout << "\nWelcome to the Numerical Integrator!\n\n";
    while(true) {
        cout << "------------------------------------------------------------------\n";
        cout << "Choose the function you would Like to Integrate. (Enter Number)\n";
        cout << "1. x^2 + 3*x + 2\n";
        cout << "2. sin(5*x)/2 + 1\n";
        cout << "3. 3 * cos(2*x) + 1\n";
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
        
        function<float(float)> func;
        
        switch(funcChoice) {
            case 1:
                func = func1;
                break;
            case 2:
                func = func2;
                break;
            case 3:
                func = func3;
                break;
            case 4:
                func = func4;
                break;
        }

        cout << "\nChoose the method you like to use to integrate the function. (Enter number)" << '\n';
        cout << "1. Trapezoidal Rule" << '\n';
        cout << "2. Simpson's 1/3 Rule" << '\n';
        cout << "3. Simpson's 3/8 Rule" << '\n';
        cout << "4. Exit" << "\n";

        int choice;
        cin >> choice;

        while(choice < 1 || choice > 5) {
            cout << "Invalid choice.\n";
            cin >> choice;
        }

        if(choice == 4) {
            cout << "Exiting...\n";
            return 0;
        }

        cout << "\nEnter the lower limit of integration: ";
        float lower_limit;
        cin >> lower_limit;
        
        cout << "Enter the upper limit of Integration: ";
        float upper_limit;
        cin >> upper_limit;
        
        while(lower_limit > upper_limit) {
            cout << "Lower Limit can't be greater than Upper Limit. (Try Again)\n\n";
            cout << "Enter the lower limit of integration: ";
            cin >> lower_limit;
            cout << "Enter the upper limit of Integration: ";
            cin >> upper_limit;
        }

        cout << "Enter the number of intervals: ";
        int intervals;
        cin >> intervals;
        while(intervals <= 0) {
            cout << "Intervals should be greater than 0. Enter Intervals Again: ";
            cin >> intervals;
        }
        
        float integ;
        switch (choice) {
            case 1:
                integ = Trapezoidal(lower_limit, upper_limit, intervals, func);
                cout << "\nIntegration (Trapezoidal) = " << integ;
                break;
            case 2:
                while(intervals % 2 != 0) {
                    cout << "For Simpson's 1/3 Rule intervals should be divisible by 2. Enter Intervals Again: ";
                    cin >> intervals;
                }
                integ = Simpson13(lower_limit, upper_limit, intervals, func);
                cout << "\nIntegration (Simpson's 1/3) = " << integ;
                break;
            case 3:
                while(intervals % 3 != 0) {
                    cout << "For Simpson's 3/8 Rule intervals should be divisible by 3. Enter Intervals Again: ";
                    cin >> intervals;
                }
                integ = Simpson38(lower_limit, upper_limit, intervals, func);
                cout << "\nIntegration (Simpson's 3/8) = " << integ;
                break;
            case 4:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice";
                break;
        }
        cout << "\n\n";
    }
    
}
