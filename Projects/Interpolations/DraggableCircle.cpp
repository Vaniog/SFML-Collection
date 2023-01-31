#include "DraggableCircle.h"
bool DraggableCircle::one_on_drag_ = false;

DraggableCircle::DraggableCircle() : sf::CircleShape() {

}
void DraggableCircle::OnFrame(const Timer& timer) {

}

void DraggableCircle::OnDraw(sf::RenderWindow& window) {
    window.draw(*this);
}

void DraggableCircle::OnEvent(sf::Event& event, const Timer& timer) {
    if (event.type == sf::Event::MouseMoved && on_drag_) {
        sf::Vector2f new_pos;
        new_pos.x = (float)event.mouseMove.x;
        new_pos.y = (float)event.mouseMove.y;

        new_pos.x = std::max(max_bounds_.left, new_pos.x);
        new_pos.y = std::max(max_bounds_.top, new_pos.y);
        new_pos.x = std::min(max_bounds_.left + max_bounds_.width, new_pos.x);
        new_pos.y = std::min(max_bounds_.top + max_bounds_.height, new_pos.y);

        sf::CircleShape::setPosition(new_pos);

    } else if (event.type == sf::Event::MouseButtonPressed && !one_on_drag_) {
        if (sf::CircleShape::getGlobalBounds().contains((float)event.mouseButton.x, (float)event.mouseButton.y)) {
            on_drag_ = true;
            one_on_drag_ = true;
        }
    } else if (event.type == sf::Event::MouseButtonReleased) {
        on_drag_ = false;
        one_on_drag_ = false;
    }
}

void DraggableCircle::SetMaxBounds(const sf::FloatRect& max_bounds) {
    max_bounds_ = max_bounds;
}
