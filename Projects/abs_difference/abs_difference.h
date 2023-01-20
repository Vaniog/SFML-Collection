#pragma once
#include "Scene.h"
#include <cmath>

float Remap(float value, float inputStart, float inputEnd, float outputStart, float outputEnd)
{
    float result = (value - inputStart)/(inputEnd - inputStart)*(outputEnd - outputStart) + outputStart;

    return result;
}

class abs_difference : public Scene {
public:
    abs_difference() {
    texture.create(window_size_.x, window_size_.y);
    sprite.setTexture(texture);
    }
    void OnFrame(const Timer& timer) override {
	    for (int i = 0; i < window_size_.x; ++i){
	        for (int j = 0; j < window_size_.y; ++j){
	            float x = Remap(i, 0, window_size_.x, -window_size_.x/2, window_size_.x/2);
	            float y = Remap(j,0,window_size_.y, -window_size_.y/2, window_size_.y/2);
	
	            float difference = (fabs(x) + fabs(y)) - fabs(x + y);
	
	            int index = (i + j*window_size_.x)*4;
	
	            int color = Remap(difference,0,limit,0,255);
	            pixels[index] = pixels[index+1] =pixels[index+2] = floor(color);
	            pixels[index+3] = 255;
	        }
	    }

	    limit = cos(timer.GetTime()/8)*window_size_.y/2;
	};
    void OnDraw(sf::RenderWindow& window) override {
        texture.update(pixels);
        sprite.setTexture(texture);
        window.draw(sprite);
    };
    void OnEvent(sf::Event& event, const Timer& timer) override {};
private:
	sf::Texture texture;
    sf::Sprite sprite;
	sf::Uint8* pixels = new sf::Uint8[(int)window_size_.x * (int)window_size_.y * 4];

	float limit = 0;

};