#pragma once
#include "Scene.h"

#include <cmath>

class CircleViewer : public Scene {
public:
    CircleViewer() {
        circle_shape_.setRadius(100);
        circle_shape_.setPosition(window_size_.x / 2, window_size_.y / 2);
    }
    void OnFrame(const Timer& timer) override {
        circle_shape_.setScale(cosf(timer.GetTime()), cosf(timer.GetTime()));
    };
    void OnDraw(sf::RenderWindow& window) override {
        window.draw(circle_shape_);
    };
    void OnEvent(sf::Event& event, const Timer& timer) override {};
private:
    sf::CircleShape circle_shape_;
};