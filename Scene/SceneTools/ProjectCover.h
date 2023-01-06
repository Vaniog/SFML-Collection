#pragma once
#include "SFML/Graphics.hpp"
#include "Scene.h"

#include <iostream>

class ProjectCover : public Scene {
public:
    explicit ProjectCover(const std::string& name);
    void OnDraw(sf::RenderWindow& window) override;
    void OnFrame(const Timer& timer) override;
    void OnEvent(sf::Event& event, const Timer& timer) override {};

    void SetPosition(float x, float y);
    void MoveTo(float x, float y, float duration_secs);
private:
    sf::Vector2f pos_;
    sf::Vector2f old_pos_{};
    sf::Vector2f new_pos_{};
    float move_duration_pass_{};
    float move_duration_{};

    void FixSizes();
    std::string name_;

    sf::Vector2f cover_size_ = {0.8, 0.7};
    float char_size_ = 0.05;
    sf::Texture texture_;
    sf::Sprite sprite_;

    sf::Font font_;
    sf::Text text_;
};