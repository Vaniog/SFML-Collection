#pragma once
#include "Animation.h"
#include "SFML/Graphics.hpp"

#include <vector>
#include <set>
#include <stdexcept>
#include <variant>

class Interpolator {
public:
    template<typename T>
    static void AddAnim(Animation<T> anim_task);
    static void Update(double delta_time);
private:
    static Interpolator instance;
    std::map<uint32_t, std::variant<Animation<int>, Animation<float>, Animation<double>>> tasks_;
};

template<typename T>
void Interpolator::AddAnim(Animation<T> anim_task) {
    if (instance.tasks_.find(anim_task.GetHash()) != instance.tasks_.end()){
        instance.tasks_.erase(anim_task.GetHash());
    }
    instance.tasks_.insert(std::make_pair(anim_task.GetHash(), anim_task));
}
