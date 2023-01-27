#include "MenuScene.h"

#include <fstream>
#include <memory>

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
    FillFolderNames();
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
    dir_scene_ = std::make_shared<DirScene>(root_directory_);
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

        FillFolderNames();
        dir_scene_ = std::make_shared<DirScene>(fs::path(root_directory_));
        return true;
    }
    return false;
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
    dir_scene_->OnDraw(window);
    window.draw(help_text_);
}

void MenuScene::OnEvent(sf::Event& event, const Timer& timer) {
    dir_scene_->OnEvent(event, timer);
}

void MenuScene::OnFrame(const Timer& timer) {
    dir_scene_->OnFrame(timer);
}

std::string MenuScene::SelectedScene() {
    return dir_scene_->SelectedScene();
}
