#include "DescriptionScene.h"

#include <fstream>
#include <sstream>
#include "Interpolator.h"

DescriptionScene::DescriptionScene() {
    font_.loadFromFile("Resources/MenuFont.ttf");

    text_.setFont(font_);
    text_.setFillColor(sf::Color::White);
}

void DescriptionScene::SetDescriptionFrom(const fs::path& proj_path) {
    auto description_path = std::filesystem::current_path() / proj_path / "description.txt";
    if (std::filesystem::exists(description_path)) {
        std::ifstream file_in(description_path);
        std::stringstream buffer;
        buffer << file_in.rdbuf();

        description_ = buffer.str();
    } else {
        description_ = "";
    }
    text_.setString(description_);
    FixSizes();
}

void DescriptionScene::FixSizes() {
    text_.setCharacterSize(static_cast<uint32_t>(window_size_.y * char_size_));
    text_.setOrigin(text_.getLocalBounds().width / 2,
                    text_.getLocalBounds().height / 2);
    text_.setPosition(pos_.x, pos_.y);

    border_.setOrigin(border_.getLocalBounds().width / 2,
                      border_.getLocalBounds().height / 2);
    border_.setSize(sf::Vector2f(text_.getGlobalBounds().width,
                                 text_.getGlobalBounds().height)
                            + sf::Vector2f(padding_,
                                           padding_));
    border_.setPosition(pos_.x, pos_.y);

    text_.setScale(scale_, scale_);
    border_.setScale(scale_, scale_);
}

void DescriptionScene::OnDraw(sf::RenderWindow& window) {
    if (text_.getString().isEmpty()) {
        return;
    }
    window.draw(border_);
    window.draw(text_);
}

void DescriptionScene::OnFrame(const Timer& timer) {
    FixSizes();
    text_.setFillColor(sf::Color(0, 0, 0, (uint8_t)(alpha_ * 255.0f)));
    border_.setFillColor(sf::Color(255, 255, 255, (uint8_t)(alpha_ * 255.0f)));
}

void DescriptionScene::OnEvent(sf::Event& event, const Timer& timer) {

}

void DescriptionScene::Show() {
    if (alpha_ == 0) {
        Interpolator::AddAnim(Animation<double>(alpha_, alpha_, 1, 0.5,
                                                [](float t) {
                                                  if (t < 0.5)
                                                      return 0.0;
                                                  return IpFuncs::EaseInOut(2 * t - 1);
                                                }));
    } else {
        Interpolator::AddAnim(Animation<double>(alpha_, alpha_, 1, 0.25, IpFuncs::EaseInOut));
    }
    Interpolator::AddAnim(Animation<float>(scale_, scale_, 1, 0.5,
                                           [](float t) {
                                             if (t < 0.5)
                                                 return 0.0;
                                             return IpFuncs::EaseInOut(2 * t - 1);
                                           }));
}
void DescriptionScene::Hide() {
    Interpolator::AddAnim(Animation<double>(alpha_, alpha_, 0, 0.3,
                                            [&](float t) {
                                              if (t < 0.5)
                                                  return 0.0;
                                              return IpFuncs::EaseInOut(2 * t - 1);
                                            }));
    Interpolator::AddAnim(Animation<float>(scale_, scale_, 0.9, 0.3));
}
