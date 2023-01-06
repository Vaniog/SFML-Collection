#pragma once
#include "Scene.h"

class CircleViewer : public Scene {
public:
    void OnFrame(const Timer& timer) override {};
    void OnDraw(sf::RenderWindow& window) override;
    void OnEvent(sf::Event& event, const Timer& timer) override {};
};