#include "IpSlider.h"

IpSlider::IpSlider(const std::function<double(double)>& IpFunction) : IpFunction_(IpFunction) {
    FixSizes();
    RestartInterpolation();
}

void IpSlider::FixSizes() {

    circle_.setRadius(circle_radius_);
    circle_.setOrigin(circle_.getGlobalBounds().width / 2, circle_.getGlobalBounds().height / 2);

    line_.setSize({width_, line_thickness_});
    line_.setOrigin(0, line_.getGlobalBounds().height / 2);
    line_.setPosition(pos_);
}

void IpSlider::OnFrame(const Timer& timer) {
    circle_.setPosition(pos_.x + circle_t_x_ * width_, pos_.y);
    time_passed_ += timer.GetDelta();
    if (time_passed_ < anim_length_)
        return;
    time_passed_ = 0;
    RestartInterpolation();
}

void IpSlider::OnDraw(sf::RenderWindow& window) {
    window.draw(line_);
    window.draw(circle_);
}

void IpSlider::OnEvent(sf::Event& event, const Timer& timer) {
}

void IpSlider::SetPosition(float x, float y) {
    pos_ = {x, y};
    FixSizes();
}

void IpSlider::SetWidth(float width) {
    width_ = width;
    FixSizes();
}
float IpSlider::GetWidth() const {
    return width_;
}

void IpSlider::RestartInterpolation() {
    if (direction_ == Direction::Right) {
        Interpolator::AddAnim(Animation<float>(circle_t_x_, 0, 1, anim_length_, IpFunction_));
        direction_ = Direction::Left;
    } else {
        Interpolator::AddAnim(Animation<float>(circle_t_x_, 1, 0, anim_length_, IpFunction_));
        direction_ = Direction::Right;
    }
}
float IpSlider::GetCircleX() const {
    return circle_.getPosition().x;
}
