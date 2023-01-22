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

    controls.setFont(font);
    controls.setString("left ,right : warping speed \n"
                       "up ,down : warping resolution");
    controls.setCharacterSize(text_size);
    controls.setFillColor(sf::Color::White);
    controls.setPosition(0, 0);

    parametres.setFont(font);
    parametres.setString("warping speed : " + std::to_string(warping_speed) + "\n"
                         "warping resolution : " + std::to_string(warping_resolution));
    parametres.setCharacterSize(text_size);
    parametres.setFillColor(sf::Color::White);
    parametres.setPosition(0, window_size_.y - 2.5*text_size);
};

void domain_warping::OnFrame(const Timer& timer) {
    for (int i = 0; i < cols; ++i) {
        for (int j = 0; j < rows; ++j) {
            // float warp_x = cos(i + 2*timer.GetTime());
            // float warp_y = sin(j + 0.5*timer.GetTime());

            float warp_x = warping.GetNoise((float)i*warping_resolution, (float)j*warping_resolution, (float)timer.GetTime()*warping_speed);
            float warp_y = warping.GetNoise((float)i*warping_resolution+100, (float)j*warping_resolution+100, (float)timer.GetTime()*warping_speed);
            float value = noise.GetNoise(i*noise_resolution + warping_implitude*warp_x, j*noise_resolution + warping_implitude*warp_y, (float)timer.GetTime()*noise_speed);

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

    window.draw(controls);
    window.draw(parametres);
};

void domain_warping::OnEvent(sf::Event& event, const Timer& timer) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
        warping_resolution += 1;
        parametres.setString("warping speed : " + std::to_string(warping_speed) + "\n"
                         "warping resolution : " + std::to_string(warping_resolution));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && warping_resolution > 0){
        warping_resolution -= 1;
        parametres.setString("warping speed : " + std::to_string(warping_speed) + "\n"
                         "warping resolution : " + std::to_string(warping_resolution));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        warping_speed += 2;
        parametres.setString("warping speed : " + std::to_string(warping_speed) + "\n"
                         "warping resolution : " + std::to_string(warping_resolution));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && warping_speed > 0){
        warping_speed -= 2;
        parametres.setString("warping speed : " + std::to_string(warping_speed) + "\n"
                         "warping resolution : " + std::to_string(warping_resolution));
    }
};