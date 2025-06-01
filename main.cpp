#include <iostream>
#include <cmath>
using namespace std;

// Change function here
const string function = "sin(x)";

// Change function here
float func(float x) {
    return sin(x);
}

float Trapezoidal(float lower_limit, float upper_limit, int intervals) {
    
    float h = (upper_limit - lower_limit) / intervals;
    
    float sum = func(lower_limit) / 2 + func(upper_limit) / 2;
    
    for(int i = 1; i < intervals; ++i) {
        sum += func(lower_limit + i*h);
    }
    
    float integral = h * sum;
    return integral;

}

float Simpson13(float lower_limit, float upper_limit, int intervals) {

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

float Simpson38(float lower_limit, float upper_limit, int intervals) {
    
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
    
    
    cout << "We will be integrating the function " << function << "\n\n";
    while(true) {

        cout << "------------------------------------------------------------------\n";
        cout << "Enter the lower limit of integration: ";
        float lower_limit;
        cin >> lower_limit;
        
        cout << "Enter the upper limit of Integration: ";
        float upper_limit;
        cin >> upper_limit;
        
        if(lower_limit > upper_limit) {
            cout << "Lower Limit can't be greater than Upper Limit. (Try Again)\n\n";
            continue;
        }

        cout << "Enter the number of intervals: ";
        int intervals;
        cin >> intervals;
        while(intervals <= 0) {
            cout << "Intervals should be greater than 0. Enter Intervals Again: ";
            cin >> intervals;
        }
        
        cout << "\nWhich method would you like to use to integrate the function? (Enter number)" << '\n';
        cout << "1. Trapezoidal Rule" << '\n';
        cout << "2. Simpson's 1/3 Rule" << '\n';
        cout << "3. Simpson's 3/8 Rule" << '\n';
        cout << "4. Exit" << "\n";

        int choice;
        cin >> choice;

        cout << '\n';
        float integ;
        switch (choice) {
            case 1:
                integ = Trapezoidal(lower_limit, upper_limit, intervals);
                cout << "Integration (Trapezoidal) = " << integ;
                break;
            case 2:
                while(intervals % 2 != 0) {
                    cout << "For Simpson's 1/3 Rule intervals should be divisible by 2. Enter Intervals Again.";
                    cin >> intervals;
                }
                integ = Simpson13(lower_limit, upper_limit, intervals);
                cout << "Integration (Simpson's 1/3) = " << integ;
                break;
            case 3:
                while(intervals % 3 != 0) {
                    cout << "For Simpson's 3/8 Rule intervals should be divisible by 3. Enter Intervals Again.";
                    cin >> intervals;
                }
                integ = Simpson38(lower_limit, upper_limit, intervals);
                cout << "Integration (Simpson's 3/8) = " << integ;
                break;
            case 4:
                return 0;
            default:
                cout << "Invalid choice";
                break;
        }
        cout << "\n\n";
    }
    
}
