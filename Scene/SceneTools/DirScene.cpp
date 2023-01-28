#include "DirScene.h"
#include "../Animation/Interpolator.h"

#include <fstream>

DirScene::DirScene(const fs::path& root_directory) {
    root_directory_ = root_directory;
    FillSceneNames();
    LoadGraphics();
}

void DirScene::FillSceneNames() {
    scene_names_.clear();
    for (auto const& dir_entry : std::filesystem::directory_iterator(root_directory_)) {
        if (dir_entry.is_directory()) {
            scene_names_.push_back(dir_entry.path().filename().string());
        }
    }
}

void DirScene::OnFrame(const Timer& timer) {
    for (auto& cover : covers_) {
        cover->OnFrame(timer);
    }
    FixSizes();
}

void DirScene::OnDraw(sf::RenderWindow& window) {
    for (auto& cover : covers_) {
        cover->OnDraw(window);
    }
}

void DirScene::OnEvent(sf::Event& event, const Timer& timer) {
    for (auto& cover : covers_) {
        cover->OnEvent(event, timer);
    }
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Down) {
            Interpolator::AddTask(AnimTask<float>(start_.y, start_.y, start_.y + size_.y * 0.1f, 0.2));
        } else if (event.key.code == sf::Keyboard::Up) {
            Interpolator::AddTask(AnimTask<float>(start_.y, start_.y, start_.y - size_.y * 0.1f, 0.2));
        }
    }
}

void DirScene::LoadGraphics() {
    covers_.clear();
    for (const auto& scene_name : scene_names_) {
        covers_.emplace_back(std::make_shared<ProjectCover>(root_directory_ / scene_name));
    }
    FixSizes();
}
void DirScene::FixSizes() {
    uint32_t row = 0;
    uint32_t col = 0;
    sf::Vector2f cover_size = {
            size_.x / (((float)covers_in_row_ + ((float)covers_in_row_ + 1) * padding.x)),
            size_.x / (((float)covers_in_row_ + ((float)covers_in_row_ + 1) * padding.x)),
    };

    for (auto& cover : covers_) {
        cover->SetSize(cover_size.x, cover_size.y);
        cover->SetPosition(start_.x + cover_size.x * (padding.x + 0.5f) + (float)col * cover_size.x * (1 + padding.x),
                           start_.y + cover_size.y * (padding.y + 0.5f) + (float)row * cover_size.y * (1 + padding.y));

        col++;
        if (col >= covers_in_row_) {
            row++;
            col = 0;
        }
    }
}
std::string DirScene::SelectedScene() {
    for (auto& cover : covers_) {
        if (cover->Pressed())
            return cover->GetName();
    }
    return "";
}

