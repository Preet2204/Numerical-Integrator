// integrator.cpp
// This Code is Written on Ubuntu
 
#include <iostream>
#include <cmath>
#include <functional>
#include <cstring>
#include <iomanip>
#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

extern "C" {
#include "tinyexpr.h"
}

using namespace std;

// Numerical Integration Methods
double Trapezoidal(double a, double b, int n, function<double(double)> f) {
    double h = (b - a) / n;
    double sum = f(a) / 2 + f(b) / 2;
    for (int i = 1; i < n; i++) sum += f(a + i * h);
    return h * sum;
}

double Simpson13(double a, double b, int n, function<double(double)> f) {
    if (n % 2 != 0) return NAN;
    double h = (b - a) / n;
    double sum = f(a) + f(b);
    for (int i = 1; i < n; i++) sum += f(a + i * h) * (i % 2 == 0 ? 2 : 4);
    return h * sum / 3;
}

double Simpson38(double a, double b, int n, function<double(double)> f) {
    if (n % 3 != 0) return NAN;
    double h = (b - a) / n;
    double sum = f(a) + f(b);
    for (int i = 1; i < n; i++) {
        sum += (i % 3 == 0 ? 2 : 3) * f(a + i * h);
    }
    return 3 * h * sum / 8;
}

// Evaluates user-defined function
function<double(double)> parseUserFunction(const char *expr, bool &valid) {
    return [exprStr = string(expr), &valid](double x) -> double {
        te_variable vars[] = { {"x", &x, 0, nullptr} };
        int err;
        te_expr *n = te_compile(exprStr.c_str(), vars, 1, &err);
        if (!n) {
            valid = false;
            return NAN;
        }
        double result = te_eval(n);
        te_free(n);
        valid = true;
        return result;
    };
}

bool isNumeric(const char* str) {
    char* end;
    strtod(str, &end);
    return *end == '\0' && str != end; // Ensures entire string is numeric
}

int main() {
    InitWindow(1000, 800, "Numerical Integrator (Raygui + TinyExpr)");
    SetTargetFPS(60);

    Font font = LoadFontEx("/usr/share/fonts/opentype/urw-base35/C059-Roman.otf", 20, 0, 250);
    Font bigFont = LoadFontEx("/usr/share/fonts/opentype/urw-base35/C059-Roman.otf", 35, 0, 250);

    GuiSetFont(font);
    GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(DARKGRAY));
    GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, ColorToInt(LIGHTGRAY));
    GuiSetStyle(BUTTON, BASE_COLOR_PRESSED, ColorToInt(GRAY));

    char functionInput[256] = "x*x + 3*x + 2";
    char lowerStr[64] = "0";
    char upperStr[64] = "10";
    char intervalsStr[64] = "120";
    
    char currentFunction[256] = "x*x + 3*x + 2";
    char currentLower[64] = "0";
    char currentUpper[64] = "10";
    
    bool validExpr = true;
    double resultTrap = 0, resultSimp13 = 0, resultSimp38 = 0;
    bool calculated = false;
    bool invalidLimits = false;
    bool invalidIntervals = false;
    int textInput = 0;

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(RAYWHITE);
        GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
        GuiSetFont(font);

        DrawTextEx(font, TextFormat("Enter function of x: %s", functionInput), {20, 20}, 20, 2.0f, DARKGRAY);
        if(GuiButton({ 340, 50, 200, 30}, "Edit Function.")) textInput = 0;

        DrawTextEx(font, TextFormat("Lower Limit: %s", lowerStr), {20, 100}, 20, 2.0f, DARKGRAY);
        if(GuiButton({ 160, 140, 200, 30}, "Edit Lower Limit.")) textInput = 1;

        DrawTextEx(font, TextFormat("Upper Limit: %s", upperStr), {20, 190}, 20, 2.0f, DARKGRAY);
        if(GuiButton({ 160, 230, 200, 30}, "Edit Upper Limit.")) textInput = 2;

        DrawTextEx(font, TextFormat("Intervals: %s", intervalsStr), {20, 280}, 20, 2.0f, DARKGRAY);
        if(GuiButton({ 160, 320, 200, 30}, "Edit Intervals.")) textInput = 3;

        switch (textInput) {
            case 0:
                GuiTextBox({ 20, 50, 300, 30 }, functionInput, 256, true);
                break;
            case 1:
                GuiTextBox({ 20, 140, 120, 30 }, lowerStr, 64, true);
                break;
            case 2:
                GuiTextBox({ 20, 230, 120, 30 }, upperStr, 64, true);
                break;
            case 3:
                GuiTextBox({ 20, 320, 120, 30 }, intervalsStr, 64, true);
                break;
        }

        if(strlen(functionInput) == 0) {
            DrawTextEx(font, "Function Input Invalid!", {500, 20}, 20, 2, RED);
        }
        
        if(strlen(lowerStr) == 0) {
            DrawTextEx(font, "Lower Limit Input is Empty!", {300, 100}, 20, 2, RED);
        }else if(!isNumeric(lowerStr)) {
            DrawTextEx(font, "Lower Limit Should be numeric!", {300, 100}, 20, 2, RED);
        }
        
        if(strlen(upperStr) == 0) {
            DrawTextEx(font, "Upper Limit Input is Empty!", {300, 190}, 20, 2, RED);
        }else if(!isNumeric(upperStr)) {
            DrawTextEx(font, "Upper Limit Should be Numeric!", {300, 190}, 20, 2, RED);
        }
        
        if(strlen(intervalsStr) == 0) {
            DrawTextEx(font, "Interval Input is Empty!", {300, 280}, 20, 2, RED);
        }else if(!isNumeric(intervalsStr)) {
            DrawTextEx(font, "Intervals Should be Numeric!", {300, 280}, 20, 2, RED);
        }

        GuiSetStyle(DEFAULT, TEXT_SIZE, 35);
        GuiSetFont(bigFont);
        if (strlen(functionInput) > 0 && strlen(lowerStr) > 0 && strlen(upperStr) > 0 
            && strlen(intervalsStr) > 0 && isNumeric(lowerStr) && isNumeric(upperStr) 
            && isNumeric(intervalsStr) && GuiButton({ 650, 190, 200, 60 }, "Integrate")) {

            double a = atof(lowerStr);
            double b = atof(upperStr);
            int n = atoi(intervalsStr);
            
            if (a > b) {
                invalidLimits = true;
                calculated = false;
            }else invalidLimits = false;
            
            if (n <= 0) {
                invalidIntervals = true;
                calculated = false;
            }else invalidIntervals = false;
            
            if (!invalidIntervals && !invalidLimits) {
                bool ok = true;
                auto f = parseUserFunction(functionInput, ok);
                validExpr = ok;
                invalidLimits = false;
                invalidIntervals = false;
                if (validExpr) {
                    resultTrap = Trapezoidal(a, b, n, f);
                    resultSimp13 = Simpson13(a, b, n, f);
                    resultSimp38 = Simpson38(a, b, n, f);
                    calculated = true;
                    strcpy(currentFunction, functionInput);
                    strcpy(currentLower, lowerStr);
                    strcpy(currentUpper, upperStr);
                }
            }
        }
        
        if (GuiButton({ 650, 270, 200, 60 }, "Reset")) {
            strcpy(functionInput, "x*x + 3*x + 2");
            strcpy(lowerStr, "0");
            strcpy(upperStr, "10");
            strcpy(intervalsStr, "120");
            calculated = false;
            validExpr = true;
            invalidLimits = false;
            invalidIntervals = false;
        }

        if (!validExpr) DrawTextEx(font, "Invalid function!", {20, 400}, 20, 2.0f, RED);

        if(invalidLimits) DrawTextEx(font, "Invalid Limits!", {20, 450}, 20, 2.0f, RED);

        if(invalidIntervals) DrawTextEx(font, "Invalid Intervals!", {20, 500}, 20, 2.0f, RED);

        if (calculated) {
            if(isnan(resultTrap) && isnan(resultSimp13) && isnan(resultSimp38)) {
                DrawTextEx(font, "Unexpected Error Occurred! (Check Input.)", {20, 400}, 20, 2.0f, RED);
            } else {
                DrawTextEx(font, TextFormat("Integration of the function %s from %s to %s.", currentFunction, currentLower, currentUpper), {20, 400}, 20, 2.0f, BLACK);
                DrawTextEx(font, TextFormat("Trapezoidal: %.6f", resultTrap), {20, 450}, 20, 2.0f, DARKGREEN);

                if (!isnan(resultSimp13))
                    DrawTextEx(font, TextFormat("Simpson 1/3: %.6f", resultSimp13), {20, 500}, 20, 2.0f, DARKGREEN);
                else
                    DrawTextEx(font, "Simpson 1/3: Invalid intervals", {20, 500}, 20, 2.0f, ORANGE);

                if (!isnan(resultSimp38))
                    DrawTextEx(font, TextFormat("Simpson 3/8: %.6f", resultSimp38), {20, 550}, 20, 2.0f, DARKGREEN);
                else
                    DrawTextEx(font, "Simpson 3/8: Invalid intervals", {20, 550}, 20, 2.0f, ORANGE);
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
