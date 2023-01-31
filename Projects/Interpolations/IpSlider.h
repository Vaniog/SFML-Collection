#pragma once
#include "Scene.h"
#include "Interpolator.h"

#include <functional>

class CustomIpExample;

class IpSlider : public Scene {
    friend CustomIpExample;
public:
    explicit IpSlider(const std::function<double(double)>& IpFunction);

    void OnFrame(const Timer& timer) override;
    void OnDraw(sf::RenderWindow& window) override;
    void OnEvent(sf::Event& event, const Timer& timer) override;

    void SetPosition(float x, float y);
    void SetWidth(float width);
    [[nodiscard]] float GetWidth() const;
    [[nodiscard]] float GetCircleX() const;
private:
    void FixSizes();

    std::function<double(double)> IpFunction_;
    enum Direction { Left, Right };
    Direction direction_ = Right;

    void RestartInterpolation();

    double time_passed_ = 0;
    const double anim_length_ = 2.0; // in seconds

    sf::Vector2f pos_ = {window_size_.x / 4, window_size_.y / 2};
    float width_ = window_size_.x / 2;

    sf::CircleShape circle_;
    const float circle_radius_ = window_size_.y * 0.02f;
    float circle_t_x_;

    sf::RectangleShape line_;
    const float line_thickness_ = window_size_.y * 0.005f;
};