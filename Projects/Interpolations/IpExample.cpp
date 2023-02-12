#include "IpExample.h"

IpExample::IpExample(const std::function<double(double)>& IpFunction, const std::string& name)
        : ip_slider_(IpFunction), ip_graph_(IpFunction) {
    font_.loadFromFile("Resources/MenuFont.ttf");
    name_text_.setFont(font_);
    name_ = name;
    name_text_.setString(name_);
    name_text_.setCharacterSize(char_size_);
    name_text_.setFillColor(sf::Color::White);
}

void IpExample::OnFrame(const Timer& timer) {
    name_text_.setString(name_);
    ip_slider_.OnFrame(timer);
    ip_graph_.OnFrame(timer);
}
void IpExample::OnEvent(sf::Event& event, const Timer& timer) {
    ip_slider_.OnEvent(event, timer);
    ip_graph_.OnEvent(event, timer);
}
void IpExample::OnDraw(sf::RenderWindow& window) {
    ip_slider_.OnDraw(window);
    ip_graph_.OnDraw(window);
    window.draw(name_text_);
}
void IpExample::FixSize() {
    ip_slider_.SetPosition(pos_.x, pos_.y);
    ip_graph_.SetPosition(pos_.x + ip_slider_.GetWidth() + margin_, pos_.y);
    name_text_.setOrigin(name_text_.getGlobalBounds().width / 2, name_text_.getGlobalBounds().height / 2);
    name_text_.setPosition(pos_.x + ip_slider_.GetWidth() + margin_ * 2 + ip_graph_.GetWidth(), pos_.y);
}
void IpExample::SetPosition(float x, float y) {
    pos_ = {x, y};
    FixSize();
}
void IpExample::SetMargin(float margin) {
    margin_ = margin;
    FixSize();
}

