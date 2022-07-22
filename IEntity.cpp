#include "IEntity.hpp"

IEntity::IEntity() { }

CollisionResult IEntity::checkCollisionWith(float x, float y, BoundingBox boundingBox)
{
    return IEntity::checkCollisionWith(this->posX, this->posY, this->collider, x, y, boundingBox);
}

CollisionResult IEntity::checkCollisionWith(IEntity* other)
{
    return this->checkCollisionWith(other->posX, other->posY, other->collider);
}

CollisionResult IEntity::checkCollisionWith(float entX, float entY, BoundingBox entBB, float otherX, float otherY, BoundingBox otherBB)
{
    CollisionResult result;
    result.entity = nullptr;
    result.target = nullptr;
    result.hasCollided = false;

    BoundingBox myBB = entBB;

    if ((entX + myBB.x > otherX) && entX < otherX + otherBB.width
        && entY + myBB.height > otherY && entY < otherY + otherBB.height) {
        result.hasCollided = true;
    }

    if (result.hasCollided) {
        if (entY < otherY + otherBB.height) {
            result.type = CollisionType::TOP;
        }
        else if (entX < otherX + otherBB.width) {
            result.type = CollisionType::RIGHT;
        }
        else if (entY + myBB.height > otherY) {
            result.type = CollisionType::BOTTOM;
        }
        else if (entX + myBB.width > otherX) {
            result.type = CollisionType::LEFT;
        }
    }

    return result;
}
