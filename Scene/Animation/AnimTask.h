#pragma once
#include "InterpolFunctions.h"

#include <functional>
#include <iostream>

template<typename T>
class AnimTask {
public:
    AnimTask(T& value,
             T start_value,
             T end_value,
             double time_length,
             std::function<double(double)> InterpolFunction = InterpolFunctions<T>::SmoothFunction);

    bool Update(double delta_time);
private:
    T start_value_;
    T end_value_;
    T* value_;
    double time_passed_ = 0;
    double time_length_;

    std::function<double(double)> InterpolFunction_;
};

template<typename T>
AnimTask<T>::AnimTask(T& value,
                      T start_value,
                      T end_value,
                      double time_length,
                      std::function<double(double)> InterpolFunction) {
    value_ = &value;
    start_value_ = start_value;
    end_value_ = end_value;
    time_length_ = time_length;

    InterpolFunction_ = InterpolFunction;
}

template<typename T>
bool AnimTask<T>::Update(double delta_time) {
    time_passed_ += delta_time;
    if (time_passed_ > time_length_) {
        *value_ = end_value_;
        return false;
    }

    *value_ = start_value_ + (end_value_ - start_value_) * InterpolFunction_(time_passed_ / time_length_);
    return true;
}
