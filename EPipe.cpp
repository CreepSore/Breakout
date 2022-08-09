#include "EPipe.hpp"

EPipe::EPipe(float width) {
    this->setWidth(width);
}

void EPipe::render(float delta, sf::RenderWindow& window) {
    auto mPos = sf::Mouse::getPosition();
    auto wPos = window.getPosition();
    this->mouseX = mPos.x - wPos.x;
    this->mouseY = mPos.y - wPos.y;
    this->posY = window.getSize().y - 25;

    auto size = this->collider.getSize();
    this->collider.setFillColor(sf::Color(255, 255, 255, 255));
    window.draw(this->collider);
}

void EPipe::tick() {
    this->posX = this->mouseX - (this->width / 2);
    this->collider.setPosition(this->posX, this->posY);
}

float EPipe::getWidth() {
    return this->width;
}

void EPipe::setWidth(float width) {
    this->width = width;
    this->collider = sf::RectangleShape(sf::Vector2f(width, 10));
}

sf::RectangleShape& EPipe::getColliderbox() {
    return this->collider;
}
