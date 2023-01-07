#pragma once
#include "Scene.h"

#include <vector>
#include <map>

class SnakeScene : public Scene {
public:
    SnakeScene();
    void OnFrame(const Timer& timer) override;
    void OnDraw(sf::RenderWindow& window) override;
    void OnEvent(sf::Event& event, const Timer& timer) override;
private:
    void StartGame();
    void EndGame();

    bool MoveSnake();
    void UpdateField();
    void ThrowApple();

    std::vector<sf::Vector2u> snake_;
    enum Direction {
        Left, Right, Up, Down
    };
    Direction snake_dir_ = Right;

    const sf::Vector2<const uint32_t> field_size_ = {15, 15};
    enum Cell {
        Empty,
        Apple,
        SnakePart
    };
    std::vector<std::vector<Cell>> field_;

    float field_size_y_ = 0.7; // in percents of height
    float cell_padding_percents_ = 0.01; // from their size;

    sf::RectangleShape cell_sprite_;
    std::map<Cell, sf::Color> cell_colors_ = {
            {Empty, sf::Color::White},
            {Apple, sf::Color::Red},
            {SnakePart, sf::Color::Green},
    };

    double default_time_per_frame = 0.2; // in secs
    double time_per_frame_; // in secs
    double time_after_last_frame_ = 0;

    sf::Text text_points_;
    sf::Font font_;
    uint32_t points_ = 0;
};