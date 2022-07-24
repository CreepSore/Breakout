#include "IEntity.hpp"

IEntity::IEntity() { }

CollisionResult IEntity::checkCollisionWith(float x, float y, BoundingBox boundingBox)
{
    return IEntity::checkCollisionWith(this->posX, this->posY, this->getColliderbox(), x, y, boundingBox);
}

CollisionResult IEntity::checkCollisionWith(IEntity* other)
{
    return this->checkCollisionWith(other->posX, other->posY, other->getColliderbox());
}

CollisionResult IEntity::checkCollisionWith(float entX, float entY, BoundingBox entBB, float otherX, float otherY, BoundingBox otherBB)
{
    CollisionResult result;
    result.entity = nullptr;
    result.target = nullptr;
    result.hasCollided = false;

    if (((entX > otherX && entX < otherX + otherBB.width) || (entX + entBB.width > otherX && entX + entBB.width < otherX + otherBB.width))
        && ((entY > otherY && entY < otherY + otherBB.height) || (entY + entBB.height > otherY && entY + entBB.height < otherY + otherBB.height))) {
        result.hasCollided = true;
    }

    if (result.hasCollided) {
        if (entY < otherY + otherBB.height) {
            result.type = CollisionType::TOP;
        }
        
        if (entX < otherX + otherBB.width) {
            result.type = CollisionType::RIGHT;
        }
        
        if (entY + entBB.height > otherY) {
            result.type = CollisionType::BOTTOM;
        }
        
        if (entX + entBB.width > otherX) {
            result.type = CollisionType::LEFT;
        }
    }

    return result;
}
