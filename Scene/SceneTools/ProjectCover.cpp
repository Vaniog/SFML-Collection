#include "ProjectCover.h"
#include <filesystem>

ProjectCover::ProjectCover(const fs::path& proj_path) {
    name_ = proj_path.filename().string();

    font_.loadFromFile("Resources/MenuFont.ttf");
    text_.setFont(font_);
    text_.setFillColor(sf::Color::White);

    auto cover_path = std::filesystem::current_path() / proj_path / "cover.png";
    if (std::filesystem::exists(cover_path)) {
        texture_.loadFromFile(cover_path.string());
    }

    sprite_.setTexture(texture_);
    sprite_.setTextureRect(sf::IntRect(0,
                                       0,
                                       static_cast<int32_t>(texture_.getSize().x),
                                       static_cast<int32_t>(texture_.getSize().y)));
    text_.setString(name_);
    FixSizes();
}

void ProjectCover::OnDraw(sf::RenderWindow& window) {
    window.draw(sprite_);
    window.draw(text_);
}

void ProjectCover::FixSizes() {
    float scale = std::min(window_size_.x * cover_size_.x / static_cast<float>(texture_.getSize().x),
                           window_size_.y * cover_size_.y / static_cast<float>(texture_.getSize().y));
    sprite_.setScale(scale, scale);
    sprite_.setOrigin(sprite_.getLocalBounds().width / 2, sprite_.getLocalBounds().height / 2);
    sprite_.setPosition(pos_.x, pos_.y);

    text_.setCharacterSize(static_cast<uint32_t>(window_size_.y * char_size_));
    text_.setOrigin(text_.getGlobalBounds().width / 2, text_.getGlobalBounds().height / 2);
    text_.setPosition(pos_.x, pos_.y + sprite_.getGlobalBounds().height / 2 + window_size_.y * char_size_);
}

void ProjectCover::SetPosition(float x, float y) {
    pos_ = {x, y};
    FixSizes();
}

void ProjectCover::SetSize(float x, float y) {

}

void ProjectCover::MoveTo(float x, float y, float duration_secs) {
    old_pos_ = pos_;
    new_pos_ = {x, y};
    move_duration_ = duration_secs;
    move_duration_pass_ = 0;
}
void ProjectCover::OnFrame(const Timer& timer) {
    if (move_duration_ == 0)
        return;
    move_duration_pass_ += static_cast<float>(timer.GetDelta());
    if (move_duration_pass_ > move_duration_) {
        move_duration_pass_ = 0;
        move_duration_ = 0;
        pos_ = new_pos_;
        FixSizes();
        return;
    }
    pos_ = old_pos_ + (new_pos_ - old_pos_) * (move_duration_pass_ / move_duration_);
    FixSizes();
}
