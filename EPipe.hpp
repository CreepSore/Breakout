#pragma once
#include <SFML\Graphics.hpp>
#include "IEntity.hpp"

class EPipe : public IEntity {
public:
    EPipe(float width = 80);
    virtual void render(float delta, sf::RenderWindow& window) override;
    virtual void tick() override;
    virtual sf::RectangleShape getColliderbox() override;

    sf::RectangleShape collider;

    int mouseX;
    int mouseY;
private:
    float width;
};
