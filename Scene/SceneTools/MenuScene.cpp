#include "MenuScene.h"

#include <fstream>

const std::string MenuScene::folders_conf_name_ = "folders.conf";
const fs::path MenuScene::default_root_directory_ = "Projects";

bool IsSubDir(fs::path p, const fs::path& root) {
    while (p != fs::path()) {
        if (p == root) {
            return true;
        }
        p = p.parent_path();
    }
    return false;
}

MenuScene::MenuScene() {
    root_directory_ = default_root_directory_;
    FillSceneNames();
    FillFolderNames();
    cur_scene_index_ = 0;
    LoadGraphics();
}

void MenuScene::LoadGraphics() {
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

bool MenuScene::ChangeDirectory(const fs::path& new_dir) {
    fs::path new_dir_abs;
    if (new_dir == "..") {
        new_dir_abs = root_directory_.parent_path();
    } else {
        new_dir_abs = root_directory_ / new_dir;
    }
    if (exists(new_dir_abs) && IsSubDir(new_dir_abs, default_root_directory_)) {
        root_directory_ = new_dir_abs;

        FillSceneNames();
        FillFolderNames();
        cur_scene_index_ = 0;
        ReloadCover(Direction::Up);
        return true;
    }
    return false;
}

void MenuScene::FillSceneNames() {
    scene_names_.clear();
    for (auto const& dir_entry : std::filesystem::directory_iterator(root_directory_)) {
        if (dir_entry.is_directory()) {
            scene_names_.push_back(dir_entry.path().filename().string());
        }
    }
}

void MenuScene::FillFolderNames() {
    folder_names_.clear();
    std::ifstream file_in(root_directory_ / folders_conf_name_);
    if (!file_in.is_open()) {
        return;
    }
    std::string s;
    while (file_in >> s) {
        folder_names_.insert(s);
    }
}

bool MenuScene::IsScene(const std::string& name) {
    return folder_names_.find(name) == folder_names_.end();
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
        ReloadCover(Direction::Right);
    }
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left) {
        cur_scene_index_--;
        cur_scene_index_ = (cur_scene_index_ + scene_names_.size()) % scene_names_.size();
        ReloadCover(Direction::Left);
    }
}

void MenuScene::OnFrame(const Timer& timer) {
    cover_->OnFrame(timer);
    old_cover_->OnFrame(timer);
}
void MenuScene::ReloadCover(const Direction& move_direction) {
    if (cover_ != nullptr) {
        old_cover_ = cover_;
        cover_ = std::make_shared<ProjectCover>(root_directory_ / scene_names_[cur_scene_index_]);
        if (move_direction != Direction::None) {
            sf::Vector2f old_move_to;
            sf::Vector2f new_pos;
            if (move_direction == Direction::Right) {
                old_move_to = {-window_size_.x, window_size_.y / 2};
                new_pos = {window_size_.x * 1.5f, window_size_.y / 2};
            } else if (move_direction == Direction::Left) {
                old_move_to = {window_size_.x * 1.5f, window_size_.y / 2};
                new_pos = {-window_size_.x, window_size_.y / 2};
            } else if (move_direction == Direction::Up) {
                old_move_to = {window_size_.x / 2, window_size_.y * 2.5f};
                new_pos = {window_size_.x / 2, -window_size_.y * 1.5f};
            }
            old_cover_->MoveTo(old_move_to.x, old_move_to.y, 0.5);
            cover_->SetPosition(new_pos.x, new_pos.y);
        } else {
            old_cover_->SetPosition(-window_size_.x, 0);
            cover_->SetPosition(window_size_.x / 2, window_size_.y / 2);
        }
        cover_->MoveTo(window_size_.x / 2, window_size_.y / 2, 0.3);
    } else {
        old_cover_ = std::make_shared<ProjectCover>(root_directory_ / scene_names_[cur_scene_index_]);
        old_cover_->SetPosition(-window_size_.x, -window_size_.y);
        cover_ = std::make_shared<ProjectCover>(root_directory_ / scene_names_[cur_scene_index_]);
        cover_->SetPosition(window_size_.x / 2, window_size_.y / 2);
    }
}
std::string MenuScene::CurSceneName() {
    return scene_names_[cur_scene_index_];
}
