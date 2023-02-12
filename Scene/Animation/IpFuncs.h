#pragma once
#include <functional>
#include <iostream>

class IpFuncs {
public:
    static double Linear(double t);
    static double EaseIn(double t);
    static double EaseOut(double t);
    static double EaseInOut(double t);

    static double EaseOutOvershoot(double t);
    static double EaseOutElastic(double t);
    static double EaseOutBounce(double t);

    static std::function<double(double)> CubicBezier(double x1, double y1, double x2, double y2);
    static std::function<double(double)> Steps(uint32_t steps);
    
    static std::function<double(double)> EaseJS;
    static std::function<double(double)> EaseInJS;
    static std::function<double(double)> EaseOutJS;
    static std::function<double(double)> EaseInOutJS;

private:
    static double CubicBezierGet(double t, double x1, double x2);
};

