#include "CustomIpExample.h"
#include <sstream>

CustomIpExample::CustomIpExample() : IpExample(IpFuncs::Linear, "CubicBezier") {
    control_circle_1_.setFillColor(sf::Color::White);
    control_circle_2_.setFillColor(sf::Color::White);

    line_to_1_[0].color = line_color_;
    line_to_1_[1].color = line_color_;
    line_to_2_[0].color = line_color_;
    line_to_2_[1].color = line_color_;

    FixSize();
}

void CustomIpExample::OnDraw(sf::RenderWindow& window) {
    window.draw(line_to_1_);
    window.draw(line_to_2_);
    window.draw(control_circle_1_);
    window.draw(control_circle_2_);
    IpExample::OnDraw(window);
}

void CustomIpExample::OnFrame(const Timer& timer) {
    IpExample::OnFrame(timer);
    FixSize();
    old_graph_transform_ = ip_graph_.graph_transform_;

    control_1_ = ip_graph_.graph_transform_.getInverse().transformPoint(control_circle_1_.getPosition());
    control_2_ = ip_graph_.graph_transform_.getInverse().transformPoint(control_circle_2_.getPosition());

    ip_graph_.IpFunction_ = IpFuncs::CubicBezier(control_1_.x, control_1_.y, control_2_.x, control_2_.y);
    ip_graph_.CountGraph();
    ip_slider_.IpFunction_ = IpFuncs::CubicBezier(control_1_.x, control_1_.y, control_2_.x, control_2_.y);

    std::stringstream values;
    values.precision(2);
    values << std::fixed << control_1_.x << ", ";
    values << std::fixed << control_1_.y << ", ";
    values << std::fixed << control_2_.x << ", ";
    values << std::fixed << control_2_.y;

    IpExample::name_text_.setString(name_text_.getString()
                                            + "\n(" + values.str() + ")");

}

void CustomIpExample::OnEvent(sf::Event& event, const Timer& timer) {
    IpExample::OnEvent(event, timer);
    control_circle_1_.OnEvent(event, timer);
    control_circle_2_.OnEvent(event, timer);
}

void CustomIpExample::FixSize() {
    control_circle_1_.setRadius(control_circle_radius_ * ip_graph_.GetWidth());
    control_circle_2_.setRadius(control_circle_radius_ * ip_graph_.GetWidth());
    control_circle_1_.setOrigin(control_circle_1_.getGlobalBounds().width / 2,
                                control_circle_1_.getGlobalBounds().height / 2);
    control_circle_2_.setOrigin(control_circle_2_.getGlobalBounds().width / 2,
                                control_circle_2_.getGlobalBounds().height / 2);

    control_circle_1_.SetMaxBounds({ip_graph_.zero_pos_.x, ip_graph_.zero_pos_.y - 2 * ip_graph_.width_,
                                    ip_graph_.width_, ip_graph_.width_ * 3});
    control_circle_2_.SetMaxBounds({ip_graph_.zero_pos_.x, ip_graph_.zero_pos_.y - 2 * ip_graph_.width_,
                                    ip_graph_.width_, ip_graph_.width_ * 3});

    control_circle_1_.setPosition(ip_graph_.graph_transform_.transformPoint
            (old_graph_transform_.getInverse().transformPoint
                    (control_circle_1_.getPosition())));
    control_circle_2_.setPosition(ip_graph_.graph_transform_.transformPoint
            (old_graph_transform_.getInverse().transformPoint
                    (control_circle_2_.getPosition())));

    line_to_1_[0].position = ip_graph_.zero_pos_;
    line_to_1_[1].position = control_circle_1_.getPosition();
    line_to_2_[0].position = ip_graph_.zero_pos_ + sf::Vector2f(ip_graph_.width_, -ip_graph_.width_);
    line_to_2_[1].position = control_circle_2_.getPosition();
}
