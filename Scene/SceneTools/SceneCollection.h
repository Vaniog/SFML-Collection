#pragma once
#include "Scene.h"
#include "SFML/Graphics.hpp"

#include <memory>
#include <vector>

class MenuScene;
class SceneCollection {
public:
    SceneCollection();
    void StartSession();
private:

    enum DisplayMode {MenuDisplay, SceneDisplay};
    DisplayMode display_mode_;

    void MainCycle(sf::RenderWindow& window);
    void OnEvent(sf::Event& event, const Timer& timer);
    bool closed_ = false;

    std::shared_ptr<MenuScene> menu_scene_;
    std::shared_ptr<Scene> cur_scene_;
    void LoadScene();
};