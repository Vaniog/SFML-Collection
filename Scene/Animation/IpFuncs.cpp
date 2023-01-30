#include "IpFuncs.h"

#include <cmath>


std::function<double(double)> IpFuncs::Ease = CubicBezier(0.25, 0.1, 0.25, 1.0);
std::function<double(double)> IpFuncs::Linear = CubicBezier(0.0, 0.0, 1.0, 1.0);
std::function<double(double)> IpFuncs::EaseOut = CubicBezier(0, 0, 0.58, 1.0);
std::function<double(double)> IpFuncs::EaseIn = CubicBezier(0.42, 0, 1.0, 1.0);
std::function<double(double)> IpFuncs::EaseInOut = CubicBezier(0.42, 0, 0.58, 1.0);

std::function<double(double)> IpFuncs::Steps(uint32_t steps) {
    return [=](double t) -> double {
      return (uint32_t)(t * (double)steps) / (double)steps;
    };
}

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
