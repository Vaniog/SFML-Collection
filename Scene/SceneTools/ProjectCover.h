#pragma once
#include "SFML/Graphics.hpp"
#include "Scene.h"

#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

class ProjectCover : public Scene {
public:
    explicit ProjectCover(const fs::path& proj_path);
    void OnDraw(sf::RenderWindow& window) override;
    void OnFrame(const Timer& timer) override;
    void OnEvent(sf::Event& event, const Timer& timer) override;

    void SetSize(float x, float y);
    void SetPosition(float x, float y);

    std::string GetName() const;
    bool Pressed() const;
private:
    bool pressed = false;

    sf::Vector2f pos_;
    sf::Vector2f old_pos_{};
    sf::Vector2f new_pos_{};
    float move_duration_pass_{};
    float move_duration_{};

    void FixSizes();
    std::string name_;
    std::string description_;

    sf::Vector2f cover_size_;
    float add_scale = 1;
    float char_size_ = 0.1;
    sf::Texture texture_;
    sf::Sprite sprite_;

    sf::Font font_;
    sf::Text name_text_;

    sf::RectangleShape description_border;
    sf::Text description_text_;
};