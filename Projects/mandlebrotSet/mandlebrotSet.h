#pragma once
#include "Scene.h"
#include <complex>
#include <cmath>

float Remap(float value, float inputStart, float inputEnd, float outputStart, float outputEnd);

class mandlebrotSet : public Scene {
public: 
    mandlebrotSet();
    void OnFrame(const Timer& timer) override{};
    void OnDraw(sf::RenderWindow& window) override;
    void OnEvent(sf::Event& event, const Timer& timer) override;
private:
    int is_in_set(std::complex<double> c);
    void campute_set();

    int width = floor(fmax(window_size_.x, window_size_.y)/2);
    int height = floor(fmin(window_size_.x, window_size_.y)/1.6);

    sf::Vector2i mouse_window_pos;

    double initial_scale = 1.5/height;

    sf::Uint8* pixels = new sf::Uint8[width * height * 4];
    
    int iteration = 40;
    double Z0_x = 0;
    double Z0_y = 0;
    double startx = -width*initial_scale;
    double endx = width*initial_scale;
    double starty = -1.5;
    double endy = 1.5;
    
    double new_startx, new_endx, new_starty, new_endy;
    
    int zoom_width = width / 2;
    int zoom_height = height / 2;

    sf::Texture texture;
    sf::Sprite sprite;
    sf::Image gradiant;

    sf::Font font;
    sf::Text controls;
    sf::Text iteration_count;
    float text_size = window_size_.y * 0.028;
};