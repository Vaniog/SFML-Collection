#pragma once
#include "Scene.h"
#include "ProjectCover.h"
#include "DirScene.h"

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
    std::string SelectedScene();
private:
    static const fs::path default_root_directory_;
    fs::path root_directory_;

    static const std::string folders_conf_name_;
    void FillFolderNames();
    std::set<std::string> folder_names_;
    std::shared_ptr<DirScene> dir_scene_;

    void LoadGraphics();
    sf::Font font_;
    sf::Text help_text_;
    float char_size_ = 0.02;
};