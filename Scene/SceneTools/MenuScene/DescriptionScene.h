#pragma once
#include "Scene.h"

#include <filesystem>

namespace fs = std::filesystem;

class DescriptionScene : Scene {

public:
    explicit DescriptionScene();
    void OnDraw(sf::RenderWindow& window) override;
    void OnFrame(const Timer& timer) override;
    void OnEvent(sf::Event& event, const Timer& timer) override;

    void SetDescriptionFrom(const fs::path& proj_path);

    void Show();
    void Hide();
private:
    sf::Vector2f pos_ = {window_size_.x / 2, window_size_.y / 2};
    void FixSizes();
    std::string description_;

    float char_size_ = 0.02;
    float scale_ = 0.9;

    sf::Font font_;
    sf::Text text_;

    double alpha_ = 0;
    float padding_ = 100;
    sf::RectangleShape border_;
};