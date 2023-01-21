#include "domain_warping.h"

domain_warping::domain_warping() {
    noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
    warping.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);


	texture.create(cols, rows);
    sprite.setTexture(texture);
    sprite.setScale(cell_size, cell_size);
    sprite.setPosition(window_size_.x/2-width/2, window_size_.y/2-height/2);
    gradiant.loadFromFile("Resources/gradient.jpg");

    font.loadFromFile("Resources/MenuFont.ttf");
};

void domain_warping::OnFrame(const Timer& timer) {
    for (int i = 0; i < cols; ++i) {
        for (int j = 0; j < rows; ++j) {
            // float warp_x = cos(i + 2*timer.GetTime());
            // float warp_y = sin(j + 0.5*timer.GetTime());

            float warp_x = warping.GetNoise((float)i, (float)j, (float)timer.GetTime()*4) ;
            float warp_y = warping.GetNoise((float)i, (float)j+100, (float)timer.GetTime()*4);
            float value = noise.GetNoise(i*scale + warping_implitude*warp_x, j*scale + warping_implitude*warp_y, (float)timer.GetTime());

            float hue = Remap(value,-1,1,0,gradiant.getSize().x);
            sf::Color color = gradiant.getPixel(floor(hue), floor(gradiant.getSize().y*0.4));

			pixels[(i + j*cols)*4 + 0] = color.r;
			pixels[(i + j*cols)*4 + 1] = color.g;
			pixels[(i + j*cols)*4 + 2] = color.b;
			pixels[(i + j*cols)*4 + 3] = 255;
        }
    }

};

void domain_warping::OnDraw(sf::RenderWindow& window) {
	texture.update(pixels);
	sprite.setTexture(texture);
	window.draw(sprite);

    // window.draw(controls);
};

void domain_warping::OnEvent(sf::Event& event, const Timer& timer) {
};