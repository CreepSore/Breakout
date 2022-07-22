#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <Windows.h>
#include <iostream>
#include "Breakout.hpp"

float tickDelay = 1000 / 60;

int main() {
    sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(800, 800), "The Game");
    Breakout* breakout = Breakout::getInstance();
    ULONGLONG lastUpdate = 0;

    while (window.isOpen()) {
        sf::Event ev;
        while (window.pollEvent(ev)) {
            breakout->onWindowEvent(ev);
            
            if (ev.type == sf::Event::Closed)
                window.close();
        }

        ULONGLONG currentTick = GetTickCount64();
        float delta = currentTick - lastUpdate;
        float renderDelta = delta / tickDelay;
        if (delta > tickDelay) {
            breakout->onTick();
            lastUpdate = currentTick;
            renderDelta = 0;
        }
        window.clear();
        breakout->onRender(renderDelta, window);
        window.display();
    }

    return 0;
}
