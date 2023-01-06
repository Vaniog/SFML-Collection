#include "MenuScene.h"
#include <filesystem>

MenuScene::MenuScene() {
    FillSceneNames();
    cur_scene_index_ = 0;
    cur_scene_changed_ = false;

    font_.loadFromFile("Resources/MenuFont.ttf");
    help_text_.setFont(font_);
    help_text_.setFillColor(sf::Color::White);
    help_text_.setString("Arrows to select\n"
                         "Enter to launch\n"
                         "In play mode, ESC to exit");
    help_text_.setPosition(0, 0);
    help_text_.setCharacterSize(window_size_.y * char_size_);
    ReloadCover();
}

void MenuScene::FillSceneNames() {
    std::filesystem::path projects_root = std::filesystem::current_path() / "Projects";
    for (auto const& dir_entry : std::filesystem::directory_iterator(projects_root)) {
        if (dir_entry.is_directory()) {
            scene_names_.push_back(dir_entry.path().filename().string());
        }
    }
}

void MenuScene::OnDraw(sf::RenderWindow& window) {
    cover_->OnDraw(window);
    old_cover_->OnDraw(window);
    window.draw(help_text_);
}

void MenuScene::OnEvent(sf::Event& event, const Timer& timer) {
    cover_->OnEvent(event, timer);
    old_cover_->OnEvent(event, timer);
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right) {
        cur_scene_index_++;
        cur_scene_index_ %= scene_names_.size();
        cur_scene_changed_ = true;
    }
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left) {
        cur_scene_index_--;
        cur_scene_index_ %= scene_names_.size();
        cur_scene_changed_ = true;
    }
}

void MenuScene::OnFrame(const Timer& timer) {
    cover_->OnFrame(timer);
    old_cover_->OnFrame(timer);
    if (cur_scene_changed_) {
        cur_scene_changed_ = false;
        ReloadCover();
    }
}

void MenuScene::ReloadCover() {
    if (cover_ != nullptr) {
        old_cover_ = cover_;
        old_cover_->MoveTo(-window_size_.x, window_size_.y / 2, 0.5);
        cover_ = std::make_shared<ProjectCover>(scene_names_[cur_scene_index_]);
        cover_->SetPosition(window_size_.x, window_size_.y / 2);
        cover_->MoveTo(window_size_.x / 2, window_size_.y / 2, 0.3);
    } else {
        old_cover_ = std::make_shared<ProjectCover>(scene_names_[cur_scene_index_]);
        old_cover_->SetPosition(-window_size_.x, -window_size_.y);
        cover_ = std::make_shared<ProjectCover>(scene_names_[cur_scene_index_]);
        cover_->SetPosition(window_size_.x / 2, window_size_.y / 2);
    }
}

std::string MenuScene::CurSceneName() {
    return scene_names_[cur_scene_index_];
}