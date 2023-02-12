#pragma once
#include "IpExample.h"
#include "CustomIpExample.h"

#include <vector>
#include <memory>

class IpField : public Scene {
public:
    IpField();

    void OnFrame(const Timer& timer) override;
    void OnDraw(sf::RenderWindow& window) override;
    void OnEvent(sf::Event& event, const Timer& timer) override;
private:
    void FixSizes();
    std::vector<std::shared_ptr<IpExample>> ip_examples_;
    void AddToExamples(const std::function<double(double)>& IpFunction, const std::string& name);

    sf::Vector2f exm_start_pos_ = {window_size_.x * 0.15f, window_size_.y * 0.1f};
    float exm_margin_y_ = window_size_.y * 0.15f;
    float exm_margin_x_ = window_size_.x * 0.1f;
    float exm_graph_width_ = window_size_.y * 0.12f;
    float exm_slider_width_ = window_size_.x * 0.5f;
    float change_for_scroll_ = exm_margin_y_ * 0.3f;

    uint32_t repeat_index_ = 0;
    sf::VertexArray repeat_line_ = sf::VertexArray(sf::LineStrip, 2);
    float line_thickness = 5;
};