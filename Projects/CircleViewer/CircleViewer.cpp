#include "CircleViewer.h"

void CircleViewer::OnDraw(sf::RenderWindow& window) {
    sf::CircleShape circle_shape(100);
    circle_shape.setPosition(window.getSize().x / 2, window.getSize().y / 2);
    window.draw(circle_shape);
}