#pragma once
#include "Scene.h"
#include "FastNoiseLite.h"
#include <cmath>

float Remap(float value, float inputStart, float inputEnd, float outputStart, float outputEnd);

class blob : public Scene {
public: 
    blob();
    void OnFrame(const Timer& timer) override;
    void OnDraw(sf::RenderWindow& window) override;
    void OnEvent(sf::Event& event, const Timer& timer) override;
private:
    const int width = window_size_.x;
    const int height = window_size_.y;
    const float PI = 3.14159265358979323846f;

    float resolution = 1;
    float speed = 12;
    int implitude = 16;
    int pt_nbr = 2000;
    int r = 200;
    float mov_angle = (2*PI)/pt_nbr;

    sf::VertexArray shape = sf::VertexArray(sf::TriangleFan, pt_nbr+1);

    FastNoiseLite noise;

    sf::Font font;
    sf::Text controls;
    float text_size = window_size_.y * 0.028;
};