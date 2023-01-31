#pragma once

#include "IpExample.h"
#include "DraggableCircle.h"

class CustomIpExample : public IpExample {
public:
    CustomIpExample();
    void OnFrame(const Timer& timer) override;
    void OnDraw(sf::RenderWindow& window) override;
    void OnEvent(sf::Event& event, const Timer& timer) override;

    ~CustomIpExample() = default;
private:
    void FixSize();

    sf::Vector2f control_1_ = {0, 0};
    double on_drag_1_ = false;
    sf::Vector2f control_2_ = {1, 1};
    double on_drag_2_ = false;

    float control_circle_radius_ = 0.08f; // from graph width
    sf::Transform old_graph_transform_;
    DraggableCircle control_circle_1_;
    DraggableCircle control_circle_2_;

    sf::Color line_color_ = sf::Color(100, 100, 100);
    sf::VertexArray line_to_1_ = sf::VertexArray(sf::LineStrip, 2);
    sf::VertexArray line_to_2_ = sf::VertexArray(sf::LineStrip, 2);
};