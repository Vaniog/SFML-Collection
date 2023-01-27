#pragma once
#include "Scene.h"
#include "ProjectCover.h"

#include <filesystem>
#include <set>
#include <memory>

namespace fs = std::filesystem;

class MenuScene : public Scene {
public:
    explicit MenuScene();
    void OnFrame(const Timer& timer) override;
    void OnDraw(sf::RenderWindow& window) override;
    void OnEvent(sf::Event& event, const Timer& timer) override;

    bool IsScene(const std::string& name);

    bool ChangeDirectory(const fs::path& new_dir);
    std::string CurSceneName();
private:
    static const fs::path default_root_directory_;
    fs::path root_directory_;
    void FillSceneNames();
    std::vector<std::string> scene_names_;

    static const std::string folders_conf_name_;
    void FillFolderNames();
    std::set<std::string> folder_names_;

    int32_t cur_scene_index_;
    void LoadGraphics();
    std::shared_ptr<ProjectCover> old_cover_;
    std::shared_ptr<ProjectCover> cover_;
    sf::Font font_;
    sf::Text help_text_;
    float char_size_ = 0.02;

    enum Direction {
        Up, Down, Left, Right, None
    };
    void ReloadCover(const Direction& move_direction = Direction::None);
};