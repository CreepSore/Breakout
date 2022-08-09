#include "./EInfoDisplay.hpp"
#include <Windows.h>
#include <string>
#include <sstream>

EInfoDisplay::EInfoDisplay() {
    this->collider = sf::RectangleShape(sf::Vector2f(0, 0));
}

void EInfoDisplay::render(float delta, sf::RenderWindow& window) {
    this->fpsCounter++;
    ULONGLONG currTick = GetTickCount64();
    if (currTick - this->lastReset > 1000) {
        this->fps = this->fpsCounter;
        this->fpsCounter = 0;
        this->lastReset = currTick;
    }

    std::stringstream str;
    std::string toDraw;
    str << "FPS: " << this->fps;
    toDraw = str.str();
    str.clear();

    sf::Text renderText = sf::Text(sf::String(toDraw), this->font);
    renderText.setPosition(2, 2);
    window.draw(renderText);
}

void EInfoDisplay::tick() {

}

sf::RectangleShape& EInfoDisplay::getColliderbox() {
    return this->collider;
}
