#pragma once
#include <SFML\Graphics.hpp>

class IRenderable {
public:
    virtual void render(float delta, sf::RenderWindow& window) = 0;
};
