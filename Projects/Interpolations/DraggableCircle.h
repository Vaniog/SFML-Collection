#pragma once
#include "SFML/Graphics.hpp"
#include "Scene.h"

class DraggableCircle : public sf::CircleShape, public Scene {
public:
    DraggableCircle();
    void OnFrame(const Timer& timer) override;
    void OnDraw(sf::RenderWindow& window) override;
    void OnEvent(sf::Event& event, const Timer& timer) override;

    void SetMaxBounds(const sf::FloatRect& max_bounds);
private:
    static bool one_on_drag_;
    bool on_drag_ = false;
    sf::FloatRect max_bounds_ = {0, 0, window_size_.x, window_size_.y};
};