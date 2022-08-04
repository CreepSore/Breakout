#include "EBlock.hpp"

EBlock::EBlock(float posX, float posY, float width, float height) {
    this->posX = posX;
    this->posY = posY;
    this->collider = sf::RectangleShape(sf::Vector2f(width, height));
    this->collider.setPosition(posX, posY);
    this->effects = std::vector<Effect>();
}

void EBlock::render(float delta, sf::RenderWindow& window)
{
    if (destroyed) return;
    auto size = this->collider.getSize();
    sf::RectangleShape body = sf::RectangleShape(sf::Vector2f(size.x, size.y));
    body.setPosition(this->posX, this->posY);
    body.setFillColor(sf::Color(255, 255, 255, 255));
    window.draw(body);
}

void EBlock::tick()
{
    if (destroyed) return;
}

void EBlock::onCollision(IEntity* collider)
{
    if (this->hasEffect(Effect::DESTROYABLE)) {
        destroyed = true;
    }

    if (this->hasEffect(Effect::DESPAWN)) {
        collider->onEvent(EventArgs("despawn"));
    }

    if (this->hasEffect(Effect::ACCELERATE)) {
        collider->onEvent(EventArgs("accelerate"));
    }
}

sf::RectangleShape EBlock::getColliderbox() {
    return this->collider;
}

bool EBlock::hasEffect(Effect effect) {
    for (Effect e : this->effects) {
        if (e == effect) {
            return true;
        }
    }
    return false;
}

void EBlock::addEffect(Effect effect) {
    if (this->hasEffect(effect)) return;
    this->effects.push_back(effect);
}

void EBlock::removeEffect(Effect effect) {
    for (int i = 0; i < this->effects.size(); i++) {
        if (this->effects[i] == effect) {
            this->effects.erase(this->effects.begin() + i);
        }
    }
}
