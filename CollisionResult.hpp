#pragma once
#include "./IEntity.hpp"

enum class CollisionType {
    NONE = -1,
    TOP = 0,
    RIGHT = 1,
    BOTTOM = 2,
    LEFT = 3,
    PIPE = 10
};

class IEntity;
struct CollisionResult {
    IEntity* entity = nullptr;
    IEntity* target = nullptr;
    sf::FloatRect intersection;
    bool hasCollided = false;
    CollisionType type = CollisionType::NONE;
};
