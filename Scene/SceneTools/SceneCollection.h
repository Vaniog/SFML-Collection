#pragma once
#include "Scene.h"
#include "SFML/Graphics.hpp"

#include <memory>
#include <vector>

class SceneCollection {
public:
    SceneCollection();
    void StartSession();
private:
    std::vector<std::string> scene_names_;
    void FillSceneNames();

    enum DisplayMode {MenuDisplay, SceneDisplay};
    DisplayMode display_mode_;

    void MainCycle(sf::RenderWindow& window);
    uint32_t cur_scene_index_;
    bool cur_scene_changed_;
    sf::Texture cur_scene_texture_;
    sf::Sprite cur_scene_sprite_;

    void MenuOnFrame(const Timer& timer);
    void ReloadSprite();
    void MenuOnDraw(sf::RenderWindow& window);
    void MenuOnEvent(sf::Event& event, const Timer& timer);

    std::shared_ptr<Scene> cur_scene_;
    void LoadScene();
    void OnFrame(const Timer& timer);
    void OnDraw(sf::RenderWindow& window);
    void OnEvent(sf::Event& event, const Timer& timer);
};