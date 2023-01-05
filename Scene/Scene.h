#pragma once
#include "SFML/Window.hpp"

class Scene {
    virtual void onFrame() = 0;
    virtual void onDraw(sf::Window& window) = 0;
    virtual void onEvent(sf::Event& event) = 0;
};