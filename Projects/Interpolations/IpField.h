#pragma once
#include "IpExample.h"

#include <vector>
#include <memory>

class IpField : public Scene {
public:
    IpField();

    void OnFrame(const Timer& timer) override;
    void OnDraw(sf::RenderWindow& window) override;
    void OnEvent(sf::Event& event, const Timer& timer) override;
private:
    std::vector<std::shared_ptr<IpExample>> ip_examples_;
    void AddToExamples(const std::function<double(double)>& IpFunction);

    sf::Vector2f exm_start_pos_ = {window_size_.x / 10, window_size_.y * 0.1f};
    float exm_margin_ = window_size_.y * 0.1f;
    float exm_width_ = window_size_.x / 2;
};