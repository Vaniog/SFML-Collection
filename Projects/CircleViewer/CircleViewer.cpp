#include "CircleViewer.h"

#include <cmath>

void CircleViewer::OnFrame(const Timer& timer) {
    double secs = timer.GetTime();
    circle_size_ = 200.0 * std::abs(cos(secs));
    circle_color_ = sf::Color(255 * std::abs(cos(secs + 2)), 255 * std::abs(cos(secs)), 255 * std::abs(cos(secs * 0.34 + 1)));

    circle_shape_.setRadius(circle_size_);
    circle_shape_.setOrigin(circle_size_, circle_size_);
    circle_shape_.setFillColor(circle_color_);
    circle_shape_.setPosition(window_size_.x / 2, window_size_.y / 2);
}

void CircleViewer::OnDraw(sf::RenderWindow& window) {
    window.draw(circle_shape_);
}
