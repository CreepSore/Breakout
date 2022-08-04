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
        float delta = (currentTick - lastUpdate) / tickDelay;
        float updateDelta = delta;
        while (updateDelta > 1) {
            breakout->onTick();
            lastUpdate = currentTick;
            updateDelta -= 1;
            delta = updateDelta;
        }
        window.clear();
        breakout->onRender(delta, window);
        window.display();
    }

    return 0;
}
