#include "InterpolFunctions.h"

double InterpolFunctions::Lerp(double a, double b, double t) {
    return a + (b - a) * t;
}

double InterpolFunctions::SmoothFunction(double t) {
    double v1 = t * t;
    double v2 = 1 - (1 - t) * (1 - t);
    return Lerp(v1, v2, t);
}

double InterpolFunctions::LinearFunction(double t) {
    return t;
}