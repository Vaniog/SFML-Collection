#include "SnakeScene.h"

SnakeScene::SnakeScene() {
    text_points_.setFillColor(sf::Color::White);
    font_.loadFromFile("Resources/MenuFont.ttf");
    text_points_.setFont(font_);
    StartGame();
}

void SnakeScene::StartGame() {
    field_.clear();
    for (uint32_t x = 0; x < field_size_.x; x++) {
        std::vector<Cell> row;
        for (uint32_t y = 0; y < field_size_.y; y++) {
            row.push_back(Empty);
        }
        field_.push_back(row);
    }

    points_ = 0;
    time_per_frame_ = default_time_per_frame;

    snake_.clear();
    snake_.emplace_back(rand() % field_size_.x, rand() % field_size_.y); // NOLINT
    UpdateField();
    ThrowApple();
}

void SnakeScene::OnFrame(const Timer& timer) {
    srand(static_cast<uint32_t>(timer.GetTime()));

    time_after_last_frame_ += timer.GetDelta();
    if (time_after_last_frame_ < time_per_frame_)
        return;
    time_after_last_frame_ = 0;

    if (!MoveSnake()) {
        EndGame();
    }
    UpdateField();
}

void SnakeScene::OnDraw(sf::RenderWindow& window) {
    float cell_width = window_size_.y * field_size_y_ / static_cast<float>(field_size_.y);
    float cell_padding = cell_width * (1 + cell_padding_percents_) * cell_padding_percents_;
    cell_width -= cell_padding;

    float start_x = (window_size_.x - window_size_.y * field_size_y_) / 2;
    float start_y = (window_size_.y - window_size_.y * field_size_y_) / 2;

    cell_sprite_.setSize({cell_width, cell_width});
    for (uint32_t x = 0; x < field_size_.x; x++) {
        for (uint32_t y = 0; y < field_size_.y; y++) {
            cell_sprite_.setFillColor(cell_colors_[field_[x][y]]);
            cell_sprite_.setPosition(start_x + (cell_width + cell_padding) * static_cast<float>(x),
                                     start_y + (cell_width + cell_padding) * static_cast<float>(y));
            window.draw(cell_sprite_);
        }
    }

    text_points_.setPosition(start_x, start_y - cell_width);
    text_points_.setString("Points: " + std::to_string(points_));
    text_points_.setCharacterSize(window_size_.y * field_size_y_ / 20);
    window.draw(text_points_);
}

void SnakeScene::OnEvent(sf::Event& event, const Timer& timer) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Right) {
            if (snake_dir_ == Direction::Left)
                return;
            snake_dir_ = Direction::Right;
        } else if (event.key.code == sf::Keyboard::Down) {
            if (snake_dir_ == Direction::Up)
                return;
            snake_dir_ = Direction::Down;
        } else if (event.key.code == sf::Keyboard::Up) {
            if (snake_dir_ == Direction::Down)
                return;
            snake_dir_ = Direction::Up;
        } else if (event.key.code == sf::Keyboard::Left) {
            if (snake_dir_ == Direction::Right)
                return;
            snake_dir_ = Direction::Left;
        }
    }
}

bool SnakeScene::MoveSnake() {
    sf::Vector2u next_cell_coords;
    if (snake_dir_ == Direction::Up) {
        next_cell_coords.x = snake_.back().x;
        next_cell_coords.y = snake_.back().y - 1;
    } else if (snake_dir_ == Direction::Down) {
        next_cell_coords.x = snake_.back().x;
        next_cell_coords.y = snake_.back().y + 1;
    } else if (snake_dir_ == Direction::Right) {
        next_cell_coords.x = snake_.back().x + 1;
        next_cell_coords.y = snake_.back().y;
    } else { // snake_dir_ == Direction::Left
        next_cell_coords.x = snake_.back().x - 1;
        next_cell_coords.y = snake_.back().y;
    }

    next_cell_coords.x = (next_cell_coords.x + field_size_.x) % field_size_.x;
    next_cell_coords.y = (next_cell_coords.y + field_size_.y) % field_size_.y;

    if (field_[next_cell_coords.x][next_cell_coords.y] == Cell::SnakePart)
        return false;
    if (field_[next_cell_coords.x][next_cell_coords.y] == Cell::Empty) {
        snake_.push_back(next_cell_coords);
        for (int32_t i = 0; i < static_cast<int32_t>(snake_.size()) - 1; i++) {
            snake_[i] = snake_[i + 1];
        }
        snake_.pop_back();
        return true;
    }
    // field_[next_cell_coords.x][next_cell_coords.y] == Cell::Apple
    snake_.push_back(next_cell_coords);
    points_++;
    time_per_frame_ *= 0.95;

    return true;
}

void SnakeScene::UpdateField() {
    for (uint32_t x = 0; x < field_size_.x; x++) {
        for (uint32_t y = 0; y < field_size_.y; y++) {
            if (field_[x][y] == Cell::SnakePart) {
                field_[x][y] = Cell::Empty;
            }
        }
    }

    bool throw_need = false;
    for (const auto segment : snake_) {
        if (field_[segment.x][segment.y] == Cell::Apple) {
            throw_need = true;
        }
        field_[segment.x][segment.y] = Cell::SnakePart;
    }
    if (throw_need)
        ThrowApple();
}

void SnakeScene::ThrowApple() {
    uint32_t x = rand() % field_size_.x; // NOLINT
    uint32_t y = rand() % field_size_.y; // NOLINT
    while (field_[x][y] != Cell::Empty) {
        x = rand() % field_size_.x; // NOLINT
        y = rand() % field_size_.y; // NOLINT
    }
    field_[x][y] = Cell::Apple;
}

void SnakeScene::EndGame() {
    StartGame();
}