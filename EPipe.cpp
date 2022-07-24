#include "EPipe.hpp"

void EPipe::render(float delta, sf::RenderWindow& window) {
    auto mPos = sf::Mouse::getPosition();
    auto wPos = window.getPosition();
    this->mouseX = mPos.x - wPos.x;
    this->mouseY = mPos.y - wPos.y;

    this->posY = window.getSize().y - 25;

    sf::RectangleShape body = sf::RectangleShape(sf::Vector2f(this->collider.width, this->collider.height));
    body.setFillColor(sf::Color(255, 255, 255, 255));
    body.setPosition(this->posX, this->posY);
    window.draw(body);
}

void EPipe::tick() {
    this->posX = this->mouseX - (this->collider.width / 2);
}

BoundingBox EPipe::getColliderbox() {
    return this->collider;
}
