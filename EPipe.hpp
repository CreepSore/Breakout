#pragma once
#include <SFML\Graphics.hpp>
#include "IEntity.hpp"

class EPipe : public IEntity {
public:
    virtual void render(float delta, sf::RenderWindow& window) override;
    virtual void tick() override;
    virtual BoundingBox getColliderbox() override;

    BoundingBox collider = BoundingBox(0, 0, 100, 10);

    int mouseX;
    int mouseY;
};
