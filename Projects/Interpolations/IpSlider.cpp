#include "IpSlider.h"

IpSlider::IpSlider(const std::function<double(double)>& IpFunction) : IpFunction_(IpFunction) {
    FixSizes();
}

void IpSlider::FixSizes() {
    circle_pos_ = pos_;

    circle_.setRadius(circle_radius_);
    circle_.setOrigin(circle_.getGlobalBounds().width / 2, circle_.getGlobalBounds().height / 2);

    line_.setSize({width_, line_thickness_});
    line_.setOrigin(0, line_.getGlobalBounds().height / 2);
    line_.setPosition(pos_);
    RestartInterpolation();
}

void IpSlider::OnFrame(const Timer& timer) {
    circle_.setPosition(circle_pos_);
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

void IpSlider::RestartInterpolation() {
    if (direction_ == Direction::Right) {
        Interpolator::AddAnim(Animation<float>(circle_pos_.x, pos_.x, pos_.x + width_, anim_length_, IpFunction_));
        direction_ = Direction::Left;
    } else {
        Interpolator::AddAnim(Animation<float>(circle_pos_.x, pos_.x + width_, pos_.x, anim_length_, IpFunction_));
        direction_ = Direction::Right;
    }
}
