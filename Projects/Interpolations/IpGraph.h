#pragma once
#include "Scene.h"
#include "Interpolator.h"

#include <memory>

class IpGraph : public Scene {
public:
    explicit IpGraph(const std::function<double(double)>& IpFunction);

    void OnFrame(const Timer& timer) override;
    void OnDraw(sf::RenderWindow& window) override;
    void OnEvent(sf::Event& event, const Timer& timer) override;

    void SetPosition(float x, float y);
    void SetWidth(float width);

private:
    void FixSizes();
    void CountGraph();

    const std::function<double(double)> IpFunction_;

    sf::Vector2f pos_;
    sf::Vector2f zero_pos_;
    float width_;

    sf::VertexArray graph_line_;
    uint32_t graph_precision_ = 50;
};