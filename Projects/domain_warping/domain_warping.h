#pragma once
#include "Scene.h"
#include "FastNoiseLite.h"
#include <cmath>

float Remap(float value, float inputStart, float inputEnd, float outputStart, float outputEnd);

class domain_warping : public Scene {
public: 
    domain_warping();
    void OnFrame(const Timer& timer) override;
    void OnDraw(sf::RenderWindow& window) override;
    void OnEvent(sf::Event& event, const Timer& timer) override;
private:
    const int width = floor(fmax(window_size_.x, window_size_.y)/2);
    const int height = floor(fmin(window_size_.x, window_size_.y)/1.6);

    float noise_resolution = 10;
    float noise_speed = 0;
    float warping_resolution = 12;
    float warping_speed = 26;
    int warping_implitude = 20;
    int cell_size = 3;

    int cols = floor(width/cell_size);
    int rows = floor(height/cell_size); 

    sf::Uint8* pixels = new sf::Uint8[width * height * 4];
    
    FastNoiseLite noise;
    FastNoiseLite warping;

    sf::Texture texture;
    sf::Sprite sprite;
    sf::Image gradiant;

    sf::Font font;
    sf::Text controls;
    sf::Text parametres;
    float text_size = window_size_.y * 0.028;
};