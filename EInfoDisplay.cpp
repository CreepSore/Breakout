#include "./EInfoDisplay.hpp"
#include <Windows.h>
#include <string>
#include <sstream>

EInfoDisplay::EInfoDisplay() {
    this->collider = sf::RectangleShape(sf::Vector2f(0, 0));
    this->lines = std::vector<std::string>();
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
    std::string toDrawFPS;
    str << "FPS: " << this->fps;
    toDrawFPS = str.str();
    str.clear();

    this->lines.insert(this->lines.begin(), toDrawFPS);

    int yOffset = 0;
    for (int i = 0; i < this->lines.size(); i++) {
        std::string toDraw = this->lines[i];
        sf::Text renderText = sf::Text(sf::String(toDraw), this->font);
        auto textBounds = renderText.getLocalBounds();
        renderText.setPosition(2, 2 + yOffset);
        yOffset = yOffset + textBounds.top + textBounds.height;
        window.draw(renderText);
    }

    this->lines.clear();
}

void EInfoDisplay::tick() {

}

void EInfoDisplay::addLine(std::string line) {
    this->lines.push_back(line);
}

sf::RectangleShape& EInfoDisplay::getColliderbox() {
    return this->collider;
}
