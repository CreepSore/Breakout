#include "Breakout.hpp"
#include <Windows.h>
#include <stdio.h>
#include <iostream>

#define BO_BLOCK_X_COUNT 10
#define BO_BLOCK_Y_COUNT 5
#define BO_ARENA_WIDTH 800
#define BO_ARENA_HEIGHT 800

Breakout* Breakout::instance = nullptr;

Breakout::Breakout() {
    this->defaultFont = sf::Font();
    this->defaultFont.loadFromFile("c:\\windows\\fonts\\arial.ttf");
    this->eInfoDisplay = EInfoDisplay();
    this->ePipe = EPipe();
    this->eBall = EBall();
    this->eBall.isSticky = true;
    this->blocks = std::vector<EBlock*>();

    EBlock* top = new EBlock(0, 0, BO_ARENA_WIDTH, 5, false);
    this->blocks.push_back(top);

    EBlock* left = new EBlock(0, 0, 5, BO_ARENA_HEIGHT, false);
    this->blocks.push_back(left);

    EBlock* right = new EBlock(BO_ARENA_WIDTH - 5, 0, 5, BO_ARENA_HEIGHT, false);
    this->blocks.push_back(right);

    int blockWidth = BO_ARENA_WIDTH / 10;
    int blockHeight = 20;
    for (int y = 0; y < BO_BLOCK_Y_COUNT; y++) {
        for (int x = 0; x < BO_BLOCK_X_COUNT; x++) {
            EBlock* block = new EBlock(x * blockWidth + (x * 2), y * blockHeight + 100 + (y * 5), blockWidth - 2, blockHeight, true);
            this->blocks.push_back(block);
        }
    }
}

void Breakout::onRender(float delta, sf::RenderWindow& window) {
    eInfoDisplay.render(delta, window);
    ePipe.render(delta, window);
    eBall.render(delta, window);

    for (EBlock* block : this->blocks) {
        block->render(delta, window);
    }
}

void Breakout::onTick() {
    eInfoDisplay.tick();
    ePipe.tick();
    eBall.tick();
    for (EBlock* block : this->blocks) {
        block->tick();
    }
}

void Breakout::onWindowEvent(sf::Event ev) {
    if (ev.type == sf::Event::MouseButtonPressed) {
        if (ev.mouseButton.button == sf::Mouse::Button::Left) {
            if (this->eBall.isSticky) {
                this->eBall.isSticky = false;
                this->eBall.shoot();

            }
            else {

            }
        }

        if (ev.mouseButton.button == sf::Mouse::Button::Right && !this->eBall.isSticky) {
            this->eBall.isSticky = true;
            this->eBall.speed = 0;
        }
    }
}

Breakout* Breakout::getInstance()
{
    Breakout::instance = Breakout::instance != nullptr ? Breakout::instance : new Breakout();
    return Breakout::instance;
}

