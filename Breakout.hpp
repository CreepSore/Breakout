#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "EInfoDisplay.hpp"
#include "EPipe.hpp"
#include "EBall.hpp"
#include "EBlock.hpp"

class Breakout {
public:
    Breakout();
    void onTick();
    void onRender(float delta, sf::RenderWindow& window);
    void onWindowEvent(sf::Event ev);

    EInfoDisplay eInfoDisplay;
    EPipe ePipe;
    EBall eBall;
    std::vector<EBlock*> blocks;

    static Breakout* instance;
    static Breakout* getInstance();
private:
    sf::Font defaultFont;
};
