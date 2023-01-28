#include "ProjectCover.h"
#include "Animation/Interpolator.h"

#include <filesystem>
#include <sstream>
#include <fstream>

ProjectCover::ProjectCover(const fs::path& proj_path) {
    name_ = proj_path.filename().string();

    font_.loadFromFile("Resources/MenuFont.ttf");
    name_text_.setFont(font_);
    name_text_.setFillColor(sf::Color::White);

    auto cover_path = std::filesystem::current_path() / proj_path / "cover.png";
    if (std::filesystem::exists(cover_path)) {
        texture_.loadFromFile(cover_path.string());
    }

    sprite_.setTexture(texture_);
    sprite_.setTextureRect(sf::IntRect(0,
                                       0,
                                       static_cast<int32_t>(texture_.getSize().x),
                                       static_cast<int32_t>(texture_.getSize().y)));
    name_text_.setString(name_);

    description_scene_ = std::make_shared<DescriptionScene>(proj_path);
    FixSizes();
}

void ProjectCover::OnDraw(sf::RenderWindow& window) {
    window.draw(sprite_);
    window.draw(name_text_);
    description_scene_->OnDraw(window);
    OnMouseMove(sf::Vector2f((float)sf::Mouse::getPosition(window).x,
                             (float)sf::Mouse::getPosition(window).y));
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
    description_scene_->OnFrame(timer);
}

void ProjectCover::OnEvent(sf::Event& event, const Timer& timer) {
}

void ProjectCover::OnMouseMove(sf::Vector2f mouse_pos) {
    if (sprite_.getGlobalBounds().contains(mouse_pos) || name_text_.getGlobalBounds().contains(mouse_pos)) {
        if (!pressed) {
            description_scene_->Show();
            Interpolator::AddTask(AnimTask<float>(add_scale, add_scale, 1.05, 0.05));
            pressed = true;
        }
    } else {
        if (pressed) {
            description_scene_->Hide();
            Interpolator::AddTask(AnimTask<float>(add_scale, add_scale, 1, 0.05));
            pressed = false;
        }
    }
    FixSizes();
}

bool ProjectCover::Pressed() const {
    return pressed;
}
std::string ProjectCover::GetName() const {
    return name_;
}
