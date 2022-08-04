#include "IEntity.hpp"

IEntity::IEntity() { }

void IEntity::onEvent(EventArgs args) { }

CollisionResult IEntity::checkCollisionWith(float x, float y, sf::RectangleShape boundingBox)
{
    return IEntity::checkCollisionWith(this->posX, this->posY, this->getColliderbox(), x, y, boundingBox);
}

CollisionResult IEntity::checkCollisionWith(IEntity* other)
{
    return this->checkCollisionWith(other->posX, other->posY, other->getColliderbox());
}

CollisionResult IEntity::checkCollisionWith(float entX, float entY, sf::RectangleShape entBB, float otherX, float otherY, sf::RectangleShape otherBB)
{
    CollisionResult result;
    result.entity = nullptr;
    result.target = nullptr;
    result.hasCollided = entBB.getGlobalBounds().intersects(otherBB.getGlobalBounds(), result.intersection);
    
    return result;
}
