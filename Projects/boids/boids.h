#pragma once
#include "Scene.h"
#include "raymath.h"
#include <cmath>

struct boid {
    sf::Vector2f pos;
    sf::Vector2f vel;
};

class boids : public Scene {
public: 
    boids();
    void OnFrame(const Timer& timer) override;
    void OnDraw(sf::RenderWindow& window) override;
    void OnEvent(sf::Event& event, const Timer& timer) override;
private:
    sf::Vector2f separation(int index);
    sf::Vector2f alignment(int index);
    sf::Vector2f cohesion(int index);

    const int WIDTH = window_size_.x;
    const int HEIGHT = window_size_.y;

    sf::Vector2f max_speed = sf::Vector2f(6, 6);
    static int const birds_nbr = 500;
    boid birds[birds_nbr];

    int separation_range = 40;
    int alignment_range = 60;
    int cohesion_range = 50;
    float turnfactor = 0.32;


    float separation_force = 0.004;
    float alignment_force = 0.01;
    float cohesion_force = 0.03;

    sf::Font font;
    sf::Text controls;
    float text_size = window_size_.y * 0.028;
};