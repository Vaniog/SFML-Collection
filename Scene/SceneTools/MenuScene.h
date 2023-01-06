#pragma once
#include "Scene.h"
#include "ProjectCover.h"

#include <memory>

class MenuScene : public Scene {
public:
    MenuScene();
    void OnFrame(const Timer& timer) override;
    void OnDraw(sf::RenderWindow& window) override;
    void OnEvent(sf::Event& event, const Timer& timer) override;

    std::string CurSceneName();
private:
    void FillSceneNames();
    std::vector<std::string> scene_names_;
    uint32_t cur_scene_index_;
    bool cur_scene_changed_;
    std::shared_ptr<ProjectCover> old_cover_;
    std::shared_ptr<ProjectCover> cover_;
    sf::Font font_;
    sf::Text help_text_;
    float char_size_ = 0.02;

    void ReloadCover();
};