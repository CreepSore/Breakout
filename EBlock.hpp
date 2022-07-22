#pragma once
#include "./IEntity.hpp"

class EBlock : public IEntity {
public:
    virtual void render(float delta, sf::RenderWindow& window) override;
    virtual void tick() override;
    void onCollision();

    bool destroyed = false;
    bool destroyable = true;
};
