#include "Interpolator.h"
#include "iostream"

Interpolator Interpolator::instance = Interpolator();

void Interpolator::Update(double delta_time) {
    for (int i = 0; i < instance.tasks_.size(); i++) {

        bool success = true;
        if (std::holds_alternative<AnimTask<int>>(instance.tasks_[i])) {
            success = std::get<AnimTask<int>>(instance.tasks_[i]).Update(delta_time);
        } else if (std::holds_alternative<AnimTask<float>>(instance.tasks_[i])) {
            success = std::get<AnimTask<float>>(instance.tasks_[i]).Update(delta_time);
        } else if (std::holds_alternative<AnimTask<double>>(instance.tasks_[i])) {
            success = std::get<AnimTask<double>>(instance.tasks_[i]).Update(delta_time);
        } else {
            throw std::runtime_error("You broke interpolator");
        }

        if (!success) {
            instance.tasks_.erase(instance.tasks_.begin() + i);
            i--;
        }
    }

}