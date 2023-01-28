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
    FixSizes();
}

void ProjectCover::OnEvent(sf::Event& event, const Timer& timer) {
    if (event.type == sf::Event::MouseMoved) {
        sf::Vector2f mouse_pos = sf::Vector2f(event.mouseMove.x, event.mouseMove.y);
        if (mouse_pos.x >= pos_.x - cover_size_.x / 2.0f &&
                mouse_pos.x <= pos_.x + cover_size_.x / 2.0f &&
                mouse_pos.y >= pos_.y - cover_size_.y / 2.0f &&
                mouse_pos.y <= pos_.y + cover_size_.y / 2.0f) {
            Interpolator::AddTask(AnimTask<float>(add_scale, add_scale, 1.05, 0.05));
            pressed = true;
        } else {
            Interpolator::AddTask(AnimTask<float>(add_scale, add_scale, 1, 0.05));
            pressed = false;
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
