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
            Interpolator::AddTask(AnimTask<float>(start_.y, start_.y, start_.y + cover_size_.y * (1 + padding_.y), 0.2));
        } else if (event.key.code == sf::Keyboard::Up) {
            Interpolator::AddTask(AnimTask<float>(start_.y, start_.y, start_.y - cover_size_.y * (1 + padding_.y), 0.2));
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
    cover_size_ = {
            size_.x / (((float)covers_in_row_ + ((float)covers_in_row_ + 1) * padding_.x)),
            size_.x / (((float)covers_in_row_ + ((float)covers_in_row_ + 1) * padding_.x)),
    };

    for (auto& cover : covers_) {
        cover->SetSize(cover_size_.x, cover_size_.y);
        cover->SetPosition(start_.x + cover_size_.x * (padding_.x + 0.5f) + (float)col * cover_size_.x * (1 + padding_.x),
                           start_.y + cover_size_.y * (padding_.y + 0.5f)
                                   + (float)row * cover_size_.y * (1 + padding_.y));

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

