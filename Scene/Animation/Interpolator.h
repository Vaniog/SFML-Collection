#pragma once
#include "AnimTask.h"
#include "SFML/Graphics.hpp"

#include <vector>
#include <stdexcept>
#include <variant>

class Interpolator {
public:
    template<typename T>
    static void AddTask(AnimTask<T> anim_task);
    static void Update(double delta_time);
private:
    static Interpolator instance;
    std::vector<std::variant<AnimTask<int>, AnimTask<float>, AnimTask<double>>> tasks_;
};

template<typename T>
void Interpolator::AddTask(AnimTask<T> anim_task) {
    instance.tasks_.push_back(anim_task);
}
