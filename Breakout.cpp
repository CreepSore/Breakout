#include "Breakout.hpp"
#include <Windows.h>
#include <stdio.h>
#include <iostream>

Breakout* Breakout::instance = nullptr;

Breakout::Breakout() {
    this->defaultFont = new sf::Font();
    this->defaultFont->loadFromFile("c:\\windows\\fonts\\arial.ttf");
    this->eInfoDisplay = EInfoDisplay();
    this->eInfoDisplay.font = *this->defaultFont;
    this->ePipe = EPipe(80.0f);
    this->eBall = new EBall();
    this->eBall->isSticky = true;
    this->blocks = std::vector<EBlock*>();
    this->additionalBalls = std::vector<EBall*>();
    this->ballDespawnQueue = std::vector<EBall*>();
}

void Breakout::initWorld() {
    int blockWidth = BO_ARENA_WIDTH / 10;
    int blockHeight = 20;
    for (int y = 0; y < BO_BLOCK_Y_COUNT; y++) {
        for (int x = 0; x < BO_BLOCK_X_COUNT; x++) {
            EBlock* block = new EBlock(x * blockWidth + (x * 2), y * blockHeight + 100 + (y * 5), blockWidth - 2, blockHeight);
            float hue = this->getNextRandom(0xFF * 0.25, 0xFF * 0.5);
            block->color = sf::Color(255, hue, hue, 255);
            block->textColor = sf::Color(255, 255, 255, 255);
            block->addEffect(Effect::DESTROYABLE);

            float hasEffect = this->getNextRandom(0, 1);
            if (hasEffect > 0.5) {
                float effectType = ceilf(this->getNextRandom(1, 4));
                if (effectType == 1) {
                    block->addEffect(Effect::P_BALL_ACCELERATE);
                    block->setText("O >>");
                }
                if (effectType == 2) {
                    block->addEffect(Effect::P_PIPE_ENLARGE);
                    block->setText("___ +");
                }
                if (effectType == 3) {
                    block->addEffect(Effect::P_PIPE_SHORTEN);
                    block->setText("___ -");
                }
                if (effectType == 4) {
                    block->addEffect(Effect::P_BALL_SPAWN);
                    block->setText("x2");
                }
            }
            this->blocks.push_back(block);
        }
    }

    EBlock* top = new EBlock(0, 0, BO_ARENA_WIDTH, 5);
    this->blocks.push_back(top);

    EBlock* left = new EBlock(0, 0, 5, BO_ARENA_HEIGHT);
    this->blocks.push_back(left);

    EBlock* right = new EBlock(BO_ARENA_WIDTH - 5, 0, 5, BO_ARENA_HEIGHT);
    this->blocks.push_back(right);

    EBlock* bottom = new EBlock(0, BO_ARENA_HEIGHT - 5, BO_ARENA_WIDTH, 5);
    bottom->addEffect(Effect::P_BALL_DESPAWN);
    this->blocks.push_back(bottom);
}

void Breakout::onRender(float delta, sf::RenderWindow& window) {
    eInfoDisplay.render(delta, window);
    ePipe.render(delta, window);
    eBall->render(delta, window);

    for (EBlock* block : this->blocks) {
        block->render(delta, window);
    }

    for (EBall* ball : this->additionalBalls) {
        ball->render(delta, window);
    }
}

void Breakout::onTick() {
    eInfoDisplay.tick();
    ePipe.tick();
    eBall->tick();
    
    for (EBall* ball : this->additionalBalls) {
        ball->tick();
    }

    for (EBlock* block : this->blocks) {
        block->tick();
    }

    for (EBall* ball : this->ballSpawnQueue) {
        this->additionalBalls.push_back(ball);
    }
    this->ballSpawnQueue.clear();

    for (EBall* ball : this->ballDespawnQueue) {
        bool despawnedMainBall = false;
        if (this->eBall == ball) {
            this->eBall->isSticky = true;
            this->eBall->speed = 0;

            if (this->additionalBalls.size() > 0) {
                delete this->eBall;
                this->eBall = this->additionalBalls.back();
                this->additionalBalls.pop_back();
            }
        }

        for (int i = 0; i < this->additionalBalls.size(); i++) {
            if (despawnedMainBall) {
                delete this->eBall;
                this->eBall = this->additionalBalls[i];
                this->additionalBalls.erase(this->additionalBalls.begin() + i);
                break;
            }

            if (this->additionalBalls[i] == ball) {
                EBall* currBall = this->additionalBalls[i];
                this->additionalBalls.erase(this->additionalBalls.begin() + i);
                i--;
                delete currBall;
            }
        }
    }
    this->ballDespawnQueue.clear();
}

void Breakout::onWindowEvent(sf::Event ev) {
    if (ev.type == sf::Event::MouseButtonPressed) {
        if (ev.mouseButton.button == sf::Mouse::Button::Left) {
            if (this->eBall->isSticky) {
                this->eBall->isSticky = false;
                this->eBall->shoot();

            }
            else {

            }
        }

        if (ev.mouseButton.button == sf::Mouse::Button::Right && !this->eBall->isSticky) {
            this->eBall->isSticky = true;
            this->eBall->speed = 0;
        }
    }
}

Breakout* Breakout::getInstance()
{
    Breakout::instance = Breakout::instance != 0 ? Breakout::instance : new Breakout();
    return Breakout::instance;
}

void Breakout::spawnBall(EBall* ball) {
    this->ballSpawnQueue.push_back(ball);
}

void Breakout::despawnBall(EBall* ball) {
    this->ballDespawnQueue.push_back(ball);
}

float Breakout::getNextRandom(float min, float max) {
    std::uniform_real_distribution distribution(min, max);
    return distribution(this->randomEngine);
}