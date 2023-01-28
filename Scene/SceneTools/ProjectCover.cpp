#include "ProjectCover.h"
#include "../Animation/Interpolator.h"

#include <filesystem>
#include <sstream>
#include <fstream>

ProjectCover::ProjectCover(const fs::path& proj_path) {
    name_ = proj_path.filename().string();

    font_.loadFromFile("Resources/MenuFont.ttf");
    name_text_.setFont(font_);
    name_text_.setFillColor(sf::Color::White);
    description_text_.setFont(font_);
    description_text_.setFillColor(sf::Color::White);

    auto cover_path = std::filesystem::current_path() / proj_path / "cover.png";
    if (std::filesystem::exists(cover_path)) {
        texture_.loadFromFile(cover_path.string());
    }

    auto description_path = std::filesystem::current_path() / proj_path / "description.txt";
    if (std::filesystem::exists(description_path)) {
        std::ifstream file_in(description_path);
        std::stringstream buffer;
        buffer << file_in.rdbuf();

        description_ = buffer.str();
    }

    sprite_.setTexture(texture_);
    sprite_.setTextureRect(sf::IntRect(0,
                                       0,
                                       static_cast<int32_t>(texture_.getSize().x),
                                       static_cast<int32_t>(texture_.getSize().y)));
    name_text_.setString(name_);
    description_text_.setString(description_);

    FixSizes();
}

void ProjectCover::OnDraw(sf::RenderWindow& window) {
    window.draw(sprite_);
    window.draw(name_text_);
    if (!description_.empty()) {
        window.draw(description_border_);
        window.draw(description_text_);
    }
}

void ProjectCover::FixSizes() {
    float scale = std::min(cover_size_.x / static_cast<float>(texture_.getSize().x),
                           cover_size_.y / static_cast<float>(texture_.getSize().y));
    sprite_.setScale(scale * add_scale, scale * add_scale);
    sprite_.setOrigin(sprite_.getLocalBounds().width / 2, sprite_.getLocalBounds().height / 2);
    sprite_.setPosition(pos_.x, pos_.y);

    name_text_.setCharacterSize(static_cast<uint32_t>(cover_size_.y * char_size_));
    name_text_.setScale(add_scale, add_scale);
    name_text_.setOrigin(name_text_.getLocalBounds().width / 2, name_text_.getLocalBounds().height / 2);
    name_text_.setPosition(pos_.x, pos_.y + cover_size_.y / 2 + cover_size_.y * char_size_ * add_scale);

    description_text_.setCharacterSize(static_cast<uint32_t>(cover_size_.y * char_size_));
    description_text_.setOrigin(description_text_.getLocalBounds().width / 2,
                                description_text_.getLocalBounds().height / 2);
    description_text_.setPosition(window_size_.x / 2, window_size_.y / 2);

    description_border_.setOrigin(description_border_.getLocalBounds().width / 2,
                                  description_border_.getLocalBounds().height / 2);
    description_border_.setSize(sf::Vector2f(description_text_.getGlobalBounds().width,
                                             description_text_.getGlobalBounds().height)
                                        + sf::Vector2f(description_padding_,
                                                       description_padding_));
    description_border_.setPosition(window_size_.x / 2, window_size_.y / 2);
}

void ProjectCover::SetPosition(float x, float y) {
    pos_ = {x, y};
    FixSizes();
}

void ProjectCover::SetSize(float x, float y) {
    cover_size_ = {x, y};
    FixSizes();
}

void ProjectCover::OnFrame(const Timer& timer) {
    description_text_.setFillColor(sf::Color(0, 0, 0, (uint8_t)(description_alpha_ * 255.0f)));
    description_border_.setFillColor(sf::Color(255, 255, 255, (uint8_t)(description_alpha_ * 255.0f)));
    FixSizes();
}

void ProjectCover::OnEvent(sf::Event& event, const Timer& timer) {
    if (event.type == sf::Event::MouseMoved) {
        sf::Vector2f mouse_pos = sf::Vector2f((float)event.mouseMove.x, (float)event.mouseMove.y);
        if (sprite_.getGlobalBounds().contains(mouse_pos) || name_text_.getGlobalBounds().contains(mouse_pos)) {
            if (!pressed) {
                Interpolator::AddTask(AnimTask<float>(add_scale, add_scale, 1.05, 0.05));
                Interpolator::AddTask(AnimTask<double>(description_alpha_, description_alpha_, 1, 0.5,
                                                       [](float t) {
                                                         if (t < 0.5)
                                                             return 0.0;
                                                         return InterpolFunctions<double>::SmoothFunction(2 * t - 1);
                                                       }));
                pressed = true;
            }
        } else {
            if (pressed) {
                Interpolator::AddTask(AnimTask<float>(add_scale, add_scale, 1, 0.05));
                Interpolator::AddTask(AnimTask<double>(description_alpha_, description_alpha_, 0, 0.5));
                pressed = false;
            }
        }
        FixSizes();
    }
}
bool ProjectCover::Pressed() const {
    return pressed;
}
std::string ProjectCover::GetName() const {
    return name_;
}
