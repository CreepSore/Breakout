#pragma once
#include "./IEntity.hpp"
#include <Windows.h>

class EInfoDisplay : public IEntity {
public:
    EInfoDisplay();
    virtual void render(float delta, sf::RenderWindow& window) override;
    virtual void tick() override;
    virtual sf::RectangleShape getColliderbox() override;
private:
    int fps = 0;
    int fpsCounter = 0;
    ULONGLONG lastReset = 0;

    sf::Font font;
};
