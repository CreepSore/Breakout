#pragma once
#include "./IRenderable.hpp"
#include "./ITickable.hpp"
#include "./BoundingBox.hpp"
#include "./CollisionResult.hpp"

struct CollisionResult;
class IEntity : IRenderable, ITickable {
public:
    IEntity();

    float posX = 0;
    float posY = 0;

    virtual BoundingBox getColliderbox() = 0;

    CollisionResult checkCollisionWith(float x, float y, BoundingBox boundingBox);
    CollisionResult checkCollisionWith(IEntity* other);

    static CollisionResult checkCollisionWith(float entX, float entY, BoundingBox entBB, float otherX, float otherY, BoundingBox otherBB);
};
