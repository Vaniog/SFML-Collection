#include "boids.h"

sf::Vector2f boids::separation(int index) {
    sf::Vector2f separation_vec(0, 0);
    for (int i = 0; i < birds_nbr; ++i){
        if (i != index && Vector2Distance(birds[index].pos , birds[i].pos) <= separation_range){
            separation_vec += (birds[index].pos - birds[i].pos);
        }
    }
    return separation_vec;
}

sf::Vector2f boids::alignment(int index) {
    sf::Vector2f alignment_vec(0,0);
    int neighbors = 0;
    for (int i = 0; i < birds_nbr; ++i){
        if (i != index && Vector2Distance(birds[index].pos , birds[i].pos) <= alignment_range){
            alignment_vec += birds[i].vel;
            neighbors++;
        }
    }
    return Vector2Normalize(alignment_vec/(float)neighbors)*max_speed.x - birds[index].vel;
}

sf::Vector2f boids::cohesion(int index) {
    sf::Vector2f cohesion_vec(0,0);
    int neighbors = 0;
    for (int i = 0; i < birds_nbr; ++i){
        if (i != index && Vector2Distance(birds[index].pos , birds[i].pos) <= cohesion_range){
            cohesion_vec += birds[i].pos;
            neighbors++;
        }
    }
    return cohesion_vec/(float)neighbors - birds[index].pos;
}

boids::boids() {
    // initial position/velocity
    for (int i = 0; i < birds_nbr; ++i){
        birds[i].pos = sf::Vector2f(rand() % WIDTH, rand() % HEIGHT);
        birds[i].vel = Vector2Normalize( sf::Vector2f(rand() % 2*WIDTH - WIDTH, rand() % 2*HEIGHT - HEIGHT) ) * 8.f;
    }

};

void boids::OnFrame(const Timer& timer) {
    for (int i = 0; i < birds_nbr; ++i){
        sf::Vector2f v1 = separation(i);
        sf::Vector2f v2 = alignment(i);
        sf::Vector2f v3 = cohesion(i);

        // if(mouse_was_pressed) {
        //     sf::Vector2f force = sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y) - birds[i].pos;
        //     birds[i].vel += Vector2Normalize(force)*2.5f;
        // }
        birds[i].vel += v1*separation_force + v2*alignment_force + v3*cohesion_force ;
        birds[i].vel = Vector2Clamp(birds[i].vel, -max_speed, max_speed);
        birds[i].pos += birds[i].vel;

        //screen edges: wrap arrond
        // {
        // if (birds[i].pos.x > WIDTH) {
        //     birds[i].pos.x = 0;
        // }
        // if (birds[i].pos.x < 0) {
        //     birds[i].pos.x = WIDTH;
        // }
        // if (birds[i].pos.y > HEIGHT) {
        //     birds[i].pos.y = 0;
        // }
        // if (birds[i].pos.y  < 0) {
        //     birds[i].pos.y = HEIGHT;
        // }
        // }

        // //screen edge: repultion force methode
        {
        if (birds[i].pos.x > WIDTH - WIDTH*0.2) {
            birds[i].vel.x -= turnfactor;
        }
        if (birds[i].pos.x < WIDTH*0.2) {
            birds[i].vel.x += turnfactor;
        }
        if (birds[i].pos.y > HEIGHT - HEIGHT*0.2) {
            birds[i].vel.y -= turnfactor;
        }
        if (birds[i].pos.y  < HEIGHT*0.2) {
            birds[i].vel.y += turnfactor;
        }
        }

    }
};

void boids::OnDraw(sf::RenderWindow& window) {
    for (int i = 0; i < birds_nbr; ++i){
        sf::ConvexShape triangle;
        triangle.setPointCount(3);
        triangle.setFillColor(sf::Color::White);
        triangle.setPoint(0, sf::Vector2f(0, -3));
        triangle.setPoint(1, sf::Vector2f(0, 3));
        triangle.setPoint(2, sf::Vector2f(10, 0));
        triangle.setRotation(RAD2DEG*Vector2Angle(sf::Vector2f(1, 0), birds[i].vel));
        triangle.setPosition(birds[i].pos);
        window.draw(triangle);
    }
};

void boids::OnEvent(sf::Event& event, const Timer& timer) {
};