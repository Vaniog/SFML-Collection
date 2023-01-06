#pragma once
#include "SFML/Graphics.hpp"
#include "SceneTools/Timer.h"

class Scene {
public:
    virtual ~Scene() {}
    virtual void OnFrame(const Timer& timer) = 0;
    virtual void OnDraw(sf::RenderWindow& window) = 0;
    virtual void OnEvent(sf::Event& event, const Timer& timer) = 0;
};