#pragma once
#include "IpSlider.h"
#include "IpGraph.h"

class IpExample : public Scene {
public:
    explicit IpExample(const std::function<double(double)>& IpFunction, const std::string& name);

    void OnFrame(const Timer& timer) override;
    void OnDraw(sf::RenderWindow& window) override;
    void OnEvent(sf::Event& event, const Timer& timer) override;

    IpSlider ip_slider_;
    IpGraph ip_graph_;

    void SetPosition(float x, float y);
    void SetMargin(float margin);
private:
    sf::Vector2f pos_ = {0, 0};

    sf::Font font_;
    const uint32_t char_size_ = (uint32_t)(window_size_.y * 0.02f);
    float margin_ = 0;
    void FixSize();
    std::string name_;
protected:
    sf::Text name_text_;
};