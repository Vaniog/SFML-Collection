#pragma once
#include "Scene.h"
#include "ProjectCover.h"

#include <filesystem>
#include <set>
#include <memory>

namespace fs = std::filesystem;

class DirScene : public Scene {
public:
    explicit DirScene(const fs::path& root_directory);
    void OnFrame(const Timer& timer) override;
    void OnDraw(sf::RenderWindow& window) override;
    void OnEvent(sf::Event& event, const Timer& timer) override;

    std::string SelectedScene();
private:
    fs::path root_directory_;
    void FillSceneNames();
    std::vector<std::string> scene_names_;

    uint32_t covers_in_row_ = 5;
    sf::Vector2f start_ = {0, 0};
    sf::Vector2f size_ = window_size_;
    sf::Vector2f padding = {0.5, 0.5}; // in percents of cover size

    void LoadGraphics();
    std::vector<std::shared_ptr<ProjectCover>> covers_;
    void FixSizes();
};