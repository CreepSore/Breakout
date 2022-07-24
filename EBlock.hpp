#pragma once
#include "./IEntity.hpp"

class EBlock : public IEntity {
public:
    EBlock(float posX, float posY, float width, float height, bool destroyable = false);
    
    virtual void render(float delta, sf::RenderWindow& window) override;
    virtual void tick() override;
    virtual BoundingBox getColliderbox() override;
    void onCollision();

    BoundingBox collider;

    bool destroyed = false;
    bool destroyable = true;
};
