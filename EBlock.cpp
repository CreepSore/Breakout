#include "EBlock.hpp"

EBlock::EBlock(float posX, float posY, float width, float height, bool destroyable) {
    this->posX = posX;
    this->posY = posY;
    this->collider = BoundingBox(0, 0, width, height);
    this->destroyable = destroyable;
}

void EBlock::render(float delta, sf::RenderWindow& window)
{
    if (destroyed) return;
    sf::RectangleShape body = sf::RectangleShape(sf::Vector2f(this->getColliderbox().width, this->getColliderbox().height));
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
        destroyed = true;
        return;
    }
}

BoundingBox EBlock::getColliderbox() {
    return this->collider;
}
