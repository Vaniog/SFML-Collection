#include "Timer.h"

Timer::Timer() {
    start_time_ = std::chrono::steady_clock::now();
    last_update_time_ = start_time_;
    delta_time_ = std::chrono::microseconds();
}
void Timer::Update() {
    delta_time_ =
            std::chrono::duration_cast<std::chrono::microseconds>(
                    std::chrono::steady_clock::now() - last_update_time_);
    last_update_time_ = std::chrono::steady_clock::now();
}
double Timer::GetDelta() const {
    return static_cast<double>(delta_time_.count()) / 1000000.0;
}

double Timer::GetTime() const {
    return static_cast<double>(
            std::chrono::duration_cast<std::chrono::microseconds>(
            last_update_time_.time_since_epoch()).count()) / 1000000.0;
}
