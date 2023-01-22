#include "blob.h"

blob::blob() {
	shape[0].position = sf::Vector2f(width/2, height/2);

	font.loadFromFile("Resources/MenuFont.ttf");

    controls.setFont(font);
    controls.setString("left ,right : speed \n"
                       "up ,down : resolution\n"
                       "W, S : implitude");
    controls.setCharacterSize(text_size);
    controls.setFillColor(sf::Color::White);
    controls.setPosition(0, 0);
}

void blob::OnFrame(const Timer& timer) {
    for (int i = 1; i <= pt_nbr; i++){
        float angle = i*mov_angle;

        float x = r*cos(angle) + width/2;
        float y = r*sin(angle) + height/2;
        float delta = Remap(noise.GetNoise(x*resolution+(float)timer.GetTime()*speed, y*resolution+(float)timer.GetTime()*speed), -1, 1, -implitude, implitude);

        shape[i].position = sf::Vector2f(x+delta*cos(angle), y+delta*sin(angle));
    }
}

void blob::OnDraw(sf::RenderWindow& window) {
	window.draw(shape);
	window.draw(controls);
}

void blob::OnEvent(sf::Event& event, const Timer& timer) {
	//speed
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        speed += 1;
    }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && speed > 0){
        speed -= 1;
    }
    //resolution
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
        resolution += 0.02;
    }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && resolution > 0){
        resolution -= 0.02;
    }
    //implitude
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
        implitude += 5;
    }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && implitude > 0){
        implitude -= 5;
    }
}