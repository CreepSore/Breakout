#include "EBlock.hpp"

void EBlock::render(float delta, sf::RenderWindow& window)
{
    if (destroyed) return;
    sf::RectangleShape body = sf::RectangleShape(sf::Vector2f(this->collider.width, this->collider.height));
    body.setPosition(this->posX, this->posY);
    body.setFillColor(sf::Color(255, 255, 255, 255));
    window.draw(body);
}

void EBlock::tick()
{
    if (destroyed) return;
}

void EBlock::onCollision()
{
    if (destroyable) {
        destroyable = false;
        return;
    }
}
