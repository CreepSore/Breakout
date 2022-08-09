#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include "EInfoDisplay.hpp"
#include "EPipe.hpp"
#include "EBall.hpp"
#include "EBlock.hpp"

#define BO_BLOCK_X_COUNT 10
#define BO_BLOCK_Y_COUNT 5
#define BO_ARENA_WIDTH 800
#define BO_ARENA_HEIGHT 800

class Breakout {
public:
    Breakout();
    void initWorld();
    void onTick();
    void onRender(float delta, sf::RenderWindow& window);
    void onWindowEvent(sf::Event ev);
    void spawnBall(EBall* ball);
    void despawnBall(EBall* ball);
    float getNextRandom(float min = 0.0f, float max = 1.0f);

    EInfoDisplay eInfoDisplay;
    EPipe ePipe;
    EBall* eBall;
    std::vector<EBlock*> blocks;
    std::vector<EBall*> additionalBalls;
    std::vector<EBall*> ballSpawnQueue;
    std::vector<EBall*> ballDespawnQueue;

    static Breakout* instance;
    static Breakout* getInstance();
    sf::Font* defaultFont;
private:
    std::default_random_engine randomEngine;
};
