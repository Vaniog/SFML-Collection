#include "SquareViewer.h"

#include <cmath>

void SquareViewer::OnFrame(const Timer& timer) {
    double secs = timer.GetTime();
    square_size_ = 400.0 * std::abs(cos(secs));
    square_color_ = sf::Color(255 * std::abs(cos(secs + 2)), 255 * std::abs(cos(secs)), 255 * std::abs(cos(secs * 0.34 + 1)));

    square_shape_.setSize(sf::Vector2f(square_size_, square_size_));
    square_shape_.setOrigin(square_size_ / 2, square_size_ / 2);
    square_shape_.setRotation(360 * std::abs(cos(secs * 0.9 + 2)));
    square_shape_.setFillColor(square_color_);
    square_shape_.setPosition(window_size_.x / 2, window_size_.y / 2);
}

void SquareViewer::OnDraw(sf::RenderWindow& window) {
    window.draw(square_shape_);
}
