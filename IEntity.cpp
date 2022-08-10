#include "IEntity.hpp"

IEntity::IEntity() { }

void IEntity::onEvent(EventArgs args) { }

CollisionResult IEntity::checkCollisionWith(sf::RectangleShape& boundingBox)
{
    return IEntity::checkCollisionWith(this->getColliderbox(), boundingBox);
}

CollisionResult IEntity::checkCollisionWith(IEntity* other)
{
    return this->checkCollisionWith(other->getColliderbox());
}

CollisionResult IEntity::checkCollisionWith(sf::RectangleShape& entBB, sf::RectangleShape& otherBB)
{
    CollisionResult result;
    result.entity = nullptr;
    result.target = nullptr;
    result.hasCollided = entBB.getGlobalBounds().intersects(otherBB.getGlobalBounds(), result.intersection);
    
    return result;
}
