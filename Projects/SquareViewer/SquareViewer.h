#pragma once
#pragma once
#include "Scene.h"

class SquareViewer : public Scene {
public:
    void OnFrame(const Timer& timer) override;
    void OnDraw(sf::RenderWindow& window) override;
    void OnEvent(sf::Event& event, const Timer& timer) override {};
private:
    sf::RectangleShape square_shape_;
    uint32_t square_size_;
    sf::Color square_color_;
};