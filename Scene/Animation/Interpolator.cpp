#include "Interpolator.h"
#include "iostream"

Interpolator Interpolator::instance = Interpolator();

void Interpolator::Update(double delta_time) {
    std::vector<uint32_t> to_delete_vec;
    for (auto& task : instance.tasks_) {
        bool success;
        uint32_t hash;
        if (std::holds_alternative<Animation<int>>(task.second)) {
            success = std::get<Animation<int>>(task.second).Update(delta_time);
            hash = std::get<Animation<int>>(task.second).GetHash();
        } else if (std::holds_alternative<Animation<float>>(task.second)) {
            success = std::get<Animation<float>>(task.second).Update(delta_time);
            hash = std::get<Animation<float>>(task.second).GetHash();
        } else if (std::holds_alternative<Animation<double>>(task.second)) {
            success = std::get<Animation<double>>(task.second).Update(delta_time);
            hash = std::get<Animation<double>>(task.second).GetHash();
        } else {
            throw std::runtime_error("You broke interpolator");
        }

        if (!success) {
            to_delete_vec.push_back(hash);
        }
    }

    for (uint32_t to_delete : to_delete_vec){
        instance.tasks_.erase(to_delete);
    }
}