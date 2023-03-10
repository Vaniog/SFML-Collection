#pragma once
#include "SFML/Graphics.hpp"
#include "Scene.h"
#include "DescriptionScene.h"

#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

class ProjectCover : public Scene {
public:
    ProjectCover(const fs::path& proj_path,
                 std::shared_ptr<DescriptionScene> description_scene);
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

    void OnMouseMove(sf::Vector2f mouse_pos);
    void FixSizes();
    const fs::path proj_path_;
    std::string name_;

    sf::Vector2f cover_size_;
    float add_scale = 1;
    float char_size_ = 0.1;
    sf::Texture texture_;
    sf::Sprite sprite_;

    sf::Font font_;
    sf::Text name_text_;

    std::shared_ptr<DescriptionScene> description_scene_;
};