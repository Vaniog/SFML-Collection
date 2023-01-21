#include "mandlebrotSet.h"

mandlebrotSet::mandlebrotSet(){
	texture.create(width, height);
    sprite.setTexture(texture);
    sprite.setPosition(window_size_.x/2-width/2, window_size_.y/2-height/2);
    gradiant.loadFromFile("Resources/gradient.jpg");


    font.loadFromFile("Resources/MenuFont.ttf");

    controls.setFont(font);
    controls.setString("click to zoom, arrows to control precision, entre to render");
    controls.setCharacterSize(24);
    controls.setFillColor(sf::Color::White);
    controls.setPosition(0, 0);

    iteration_count.setFont(font);
    iteration_count.setString("iteration : " + std::to_string(iteration));
    iteration_count.setCharacterSize(24);
    iteration_count.setFillColor(sf::Color::White);
    iteration_count.setPosition(0, window_size_.y - 24);
};

int mandlebrotSet::is_in_set(std::complex<double> c) {
    std::complex<double> z (Z0_x, Z0_y);

    for (int i = 0; i < iteration; ++i){
        z = pow(z, 2) + c;
        if(std::abs(z) >= 2) {
            return i;
        }
    }
    return iteration;
};

void mandlebrotSet::campute_set() {
    for (int i = 0; i < width; ++i){
        for (int j = 0; j < height; ++j){
            double x = Remap(i,0,width,startx, endx);
            double y = Remap(j,0,height,starty, endy);

            std::complex<double> nbr (x, y);

            int iter_nbr = is_in_set(nbr);
            // std::cout << std::to_string(iter_nbr) + " \n";


            int index = (i + j*width)*4;
            if(iter_nbr == iteration) {
                pixels[index] = pixels[index+1] =pixels[index+2] = 0;
            }else {
            		//HUE COLORING
                float hue = floor(Remap(iter_nbr,0,iteration,0,gradiant.getSize().x));
                sf::Color color = gradiant.getPixel(hue, floor(gradiant.getSize().y*0.4));

                pixels[index+0] = color.r;
                pixels[index+1] = color.g;
                pixels[index+2] = color.b;

                    // SQRT COLORING

                // float bright = Remap(iter_nbr,0,iteration,0,1);
                // pixels[index] = pixels[index+1] =pixels[index+2] = Remap(sqrt(bright),0,1,0,255);

                    //  smt related to hue?
                // float hue = (iter_nbr / 1 ) - floor(iter_nbr / 1);
                // color::hsv<double> h( { hue, 80, 50 } );
                // color::rgb<double> r;
                // r = h;

                // pixels[index+0] = floor(::color::get::red( r )*255);
                // pixels[index+1] = floor(::color::get::green( r )*255);
                // pixels[index+2] = floor(::color::get::blue( r )*255);

            }
            pixels[index+3] = 255;
        }
    }

};

void mandlebrotSet::OnEvent(sf::Event& event, const Timer& timer) {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		if (mouse_window_pos.x>(window_size_.x/2 - width/2) && mouse_window_pos.x<(window_size_.x/2 + width/2) &&
			mouse_window_pos.y>(window_size_.y/2 - height/2) && mouse_window_pos.y<(window_size_.y/2 + height/2))
		{
	    sf::Vector2i mouse_pos = sf::Vector2i(Remap(mouse_window_pos.x,(window_size_.x/2 - width/2),(window_size_.x/2 + width/2),0,width)
                                             ,Remap(mouse_window_pos.y,(window_size_.y/2 - height/2),(window_size_.y/2 + height/2),0,height));

        new_startx = Remap(mouse_pos.x - zoom_width/2,0,width,startx, endx);
        // std::cout << std::to_string(new_startx) + " ";
        new_endx = Remap(mouse_pos.x + zoom_width/2,0,width,startx, endx);
        // std::cout << std::to_string(new_endx) + " \n";
        new_starty = Remap(mouse_pos.y - zoom_height/2,0,height,starty, endy);
        // std::cout << std::to_string(new_starty) + " ";
       new_endy = Remap(mouse_pos.y + zoom_height/2,0,height,starty, endy);
       // std::cout << std::to_string(endx) + " \n";

		startx = new_startx;
		endx = new_endx;
		starty  =  new_starty;
		endy = new_endy;

	    campute_set();
    	}
	}
	//iteration count control
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && iteration >= 0){
	    iteration += 20;
        iteration_count.setString("iteration : " + std::to_string(iteration));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && iteration > 0){
	    iteration -= 20;
        iteration_count.setString("iteration : " + std::to_string(iteration));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
	    campute_set();
	}
};

void mandlebrotSet::OnDraw(sf::RenderWindow& window) {
	texture.update(pixels);
	sprite.setTexture(texture);
	window.draw(sprite);

    window.draw(controls);
    window.draw(iteration_count);

    mouse_window_pos = sf::Mouse::getPosition(window);
};
