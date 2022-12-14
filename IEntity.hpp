#pragma once
#include "./IRenderable.hpp"
#include "./ITickable.hpp"
#include "./BoundingBox.hpp"
#include "./CollisionResult.hpp"
#include "./EventArgs.hpp"

struct CollisionResult;
class IEntity : IRenderable, ITickable {
public:
    IEntity();

    float posX = 0;
    float posY = 0;

    virtual sf::RectangleShape& getColliderbox() = 0;
    virtual void onEvent(EventArgs args);

    CollisionResult checkCollisionWith(sf::RectangleShape& boundingBox);
    CollisionResult checkCollisionWith(IEntity* other);

    static CollisionResult checkCollisionWith(sf::RectangleShape& entBB, sf::RectangleShape& otherBB);
};
