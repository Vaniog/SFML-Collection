#include "DescriptionScene.h"

#include <fstream>
#include <sstream>
#include "Interpolator.h"

DescriptionScene::DescriptionScene(const fs::path& proj_path) {
    font_.loadFromFile("Resources/MenuFont.ttf");

    text_.setFont(font_);
    text_.setFillColor(sf::Color::White);

    auto description_path = std::filesystem::current_path() / proj_path / "description.txt";
    if (std::filesystem::exists(description_path)) {
        std::ifstream file_in(description_path);
        std::stringstream buffer;
        buffer << file_in.rdbuf();

        description_ = buffer.str();
    }

    text_.setString(description_);
}

void DescriptionScene::FixSizes() {

    text_.setCharacterSize(static_cast<uint32_t>(window_size_.y * char_size_));
    text_.setOrigin(text_.getLocalBounds().width / 2,
                    text_.getLocalBounds().height / 2);
    text_.setPosition(window_size_.x / 2, window_size_.y / 2);

    border_.setOrigin(border_.getLocalBounds().width / 2,
                      border_.getLocalBounds().height / 2);
    border_.setSize(sf::Vector2f(text_.getGlobalBounds().width,
                                 text_.getGlobalBounds().height)
                            + sf::Vector2f(padding_,
                                           padding_));
    border_.setPosition(window_size_.x / 2, window_size_.y / 2);

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
    Interpolator::AddTask(AnimTask<double>(alpha_, alpha_, 1, 0.5,
                                           [](float t) {
                                             if (t < 0.5)
                                                 return 0.0;
                                             return InterpolFunctions<double>::SmoothFunction(2 * t - 1);
                                           }));
    Interpolator::AddTask(AnimTask<float>(scale_, scale_, 1, 0.5,
                                          [](float t) {
                                             if (t < 0.5)
                                                 return 0.0;
                                             return InterpolFunctions<double>::SmoothFunction(2 * t - 1);
                                           }));
}

void DescriptionScene::Hide() {
    Interpolator::AddTask(AnimTask<double>(alpha_, alpha_, 0, 0.3));
    Interpolator::AddTask(AnimTask<float>(scale_, scale_, 0.9, 0.3));
}
