#pragma once
#include <functional>
#include <iostream>

class IpFuncs {
public:
    static std::function<double(double)> CubicBezier(double x1, double y1, double x2, double y2);
    static std::function<double(double)> Steps(uint32_t steps);

    static std::function<double(double)> Linear;
    static std::function<double(double)> Ease;
    static std::function<double(double)> EaseInOut;
    static std::function<double(double)> EaseIn;
    static std::function<double(double)> EaseOut;
private:
    static double CubicBezierGet(double t, double x1, double x2);
};

