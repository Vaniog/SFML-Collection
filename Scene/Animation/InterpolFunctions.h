#pragma once
class InterpolFunctions {
public:
    static double LinearFunction(double t);
    static double SmoothFunction(double t);
private:
    static double Lerp(double a, double b, double t);
};

