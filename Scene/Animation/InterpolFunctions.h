#pragma once
template<typename T>
class InterpolFunctions {
public:
    static T LinearFunction(double t);
    static T SmoothFunction(double t);
private:
    static T Lerp(T a, T b, T t);
};
template<typename T>
T InterpolFunctions<T>::Lerp(T a, T b, T t) {
    return a + (b - a) * t;
}
template<typename T>
T InterpolFunctions<T>::SmoothFunction(double t) {
    double v1 = t * t;
    double v2 = 1 - (1 - t) * (1 - t);
    return Lerp(v1, v2, t);
}

template<typename T>
T InterpolFunctions<T>::LinearFunction(double t) {
    return t;
}