#pragma once
#include "Scene.h"
#include "Interpolator.h"

#include <memory>

class CustomIpExample;

class IpGraph : public Scene {
    friend CustomIpExample;
public:
    explicit IpGraph(const std::function<double(double)>& IpFunction);

    void OnFrame(const Timer& timer) override;
    void OnDraw(sf::RenderWindow& window) override;
    void OnEvent(sf::Event& event, const Timer& timer) override;

    void SetPosition(float x, float y);
    void SetWidth(float width);
    [[nodiscard]] float GetWidth() const;
private:
    void FixSizes();
    void CountGraph();

    std::function<double(double)> IpFunction_;

    sf::Vector2f pos_;
    sf::Vector2f zero_pos_;
    float width_;

    sf::VertexArray graph_line_;
    uint32_t graph_precision_ = 50;
    sf::Transform graph_transform_;
};