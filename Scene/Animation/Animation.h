#pragma once
#include "IpFuncs.h"

#include <functional>
#include <iostream>
#include <utility>

template<typename T>
class Animation {
public:
    Animation(T& value,
              T start_value,
              T end_value,
              double time_length,
              const std::function<double(double)>& InterpolFunction = IpFuncs::Ease);

    bool Update(double delta_time);

    uintptr_t GetHash();
    bool operator==(const Animation<T>& anim_task);
    bool operator<(const Animation<T>& anim_task);
private:
    T start_value_;
    T end_value_;
    T* value_;
    double time_passed_ = 0;
    double time_length_;

    std::function<double(double)> InterpolFunction_;
};

template<typename T>
uintptr_t Animation<T>::GetHash() {
    return reinterpret_cast<uintptr_t>(value_);
}
template<typename T>
bool Animation<T>::operator<(const Animation<T>& anim_task) {
    return anim_task.GetHash() < GetHash();
}
template<typename T>
bool Animation<T>::operator==(const Animation<T>& anim_task) {
    return anim_task.GetHash() == GetHash();
}

template<typename T>
Animation<T>::Animation(T& value,
                        T start_value,
                        T end_value,
                        double time_length,
                        const std::function<double(double)>& InterpolFunction) {
    value_ = &value;
    start_value_ = start_value;
    end_value_ = end_value;
    time_length_ = time_length;

    InterpolFunction_ = InterpolFunction;
}

template<typename T>
bool Animation<T>::Update(double delta_time) {
    time_passed_ += delta_time;
    if (time_passed_ > time_length_) {
        *value_ = end_value_;
        return false;
    }

    *value_ = start_value_ + (end_value_ - start_value_) * InterpolFunction_(time_passed_ / time_length_);
    return true;
}
