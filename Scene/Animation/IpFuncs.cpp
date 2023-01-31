#include "IpFuncs.h"

#include <cmath>

double IpFuncs::Linear(double t) {
    return t;
}
double IpFuncs::EaseIn(double t) {
    return t * t;
}

double IpFuncs::EaseOut(double t) {
    return 1 - (1 - t) * (1 - t);
}

double IpFuncs::EaseInOut(double t) {
    if (t < 0.5)
        return 2.0 * t * t;
    else {
        return 1 - 2.0 * (1 - t) * (1 - t);
    }
}

double IpFuncs::EaseOutOvershoot(double t) {
    const double c1 = 1.70158f;
    const double c3 = c1 + 1;
    const double z = t - 1;
    return 1 + c3 * z * z * z + c1 * z * z;
}

double IpFuncs::EaseOutElastic(double t) {
    if (t == 0 || t == 1)
        return t;

    const double c4 = (2 * M_PI) / 3;
    return
            pow(2, -10 * t) *
                    sin((t * 10 - 0.75f) * c4) + 1;
}

double IpFuncs::EaseOutBounce(double t) {
    const double n1 = 7.5625;
    const double d1 = 2.75;
    if (t < 1 / d1)
        return n1 * t * t;
    else if (t < 2 / d1) {
        t -= 1.5 / d1;
        return n1 * t * t + 0.75;
    } else if (t < 2.5f / d1) {
        t -= 2.25 / d1;
        return n1 * t * t + 0.9375;
    } else {
        t -= 2.625 / d1;
        return n1 * t * t + 0.984375;
    }

}

std::function<double(double)> IpFuncs::Steps(uint32_t steps) {
    return [=](double t) -> double {
      return (uint32_t)(t * (double)steps) / (double)steps;
    };
}
std::function<double(double)> IpFuncs::EaseJS = CubicBezier(0.25, 0.1, 0.25, 1.0);
std::function<double(double)> IpFuncs::EaseOutJS = CubicBezier(0, 0, 0.58, 1.0);
std::function<double(double)> IpFuncs::EaseInJS = CubicBezier(0.42, 0, 1.0, 1.0);
std::function<double(double)> IpFuncs::EaseInOutJS = CubicBezier(0.42, 0, 0.58, 1.0);

std::function<double(double)> IpFuncs::CubicBezier(double x1, double y1, double x2, double y2) {
    std::function<double(double)> cubic_bezier = [=](double t) -> double {
      int depth = 20;
      double l = 0;
      double r = 1;
      while (depth--) {
          double m = (l + r) / 2;
          if (CubicBezierGet(m, x1, x2) < t)
              l = m;
          else
              r = m;
      }
      return CubicBezierGet(l, y1, y2);
    };
    return cubic_bezier;
}
double IpFuncs::CubicBezierGet(double t, double x1, double x2) {
    return (1 - t) * (1 - t) * (1 - t) * 0.0 +
            3 * (1 - t) * (1 - t) * t * x1 +
            3 * (1 - t) * t * t * x2 +
            t * t * t * 1.0;
}
