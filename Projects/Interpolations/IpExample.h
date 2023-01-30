#pragma once
#include "IpSlider.h"
#include "IpGraph.h"

class IpExample : public Scene {
public:
    explicit IpExample(const std::function<double(double)>& IpFunction);

    void OnFrame(const Timer& timer) override;
    void OnDraw(sf::RenderWindow& window) override;
    void OnEvent(sf::Event& event, const Timer& timer) override;

    IpSlider ip_slider_;
    IpGraph ip_graph_;
private:
};