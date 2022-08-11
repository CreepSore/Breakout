#include "EBlock.hpp"
#include "Breakout.hpp"

EBlock::EBlock(float posX, float posY, float width, float height) {
    this->posX = posX;
    this->posY = posY;

    this->collider = sf::RectangleShape(sf::Vector2f(width, height));
    this->collider.setPosition(posX, posY);

    this->body = sf::RectangleShape(sf::Vector2f(width, height));
    this->body.setPosition(posX, posY);

    this->effects = std::vector<Effect>();
    this->color = sf::Color(255, 255, 255, 255);
    this->textColor = sf::Color(0, 0, 0, 255);
}

void EBlock::render(float delta, sf::RenderWindow& window)
{
    if (destroyed) return;
    auto size = this->collider.getSize();
    this->body.setFillColor(this->color);
    window.draw(this->body);
    
    if (this->hasText) {
        this->text.setFillColor(this->textColor);
        window.draw(this->text);
    }
}

void EBlock::tick()
{
    if (destroyed) return;
}

void EBlock::onCollision(IEntity* collider)
{
    Breakout* game = Breakout::getInstance();
    if (this->hasEffect(Effect::DESTROYABLE)) {
        destroyed = true;
    }

    if (this->hasEffect(Effect::P_BALL_SPAWN)) {
        EBall* colliderBall = (EBall*)collider;
        EBall* ball = new EBall();
        ball->posX = colliderBall->posX;
        ball->posY = colliderBall->posY;
        ball->direction = colliderBall->direction + game->getNextRandom(-10, 10);
        ball->speed = BO_DEFAULT_BALL_SPEED;
        game->spawnBall(ball);
    }

    if (this->hasEffect(Effect::P_BALL_DESPAWN)) {
        game->despawnBall((EBall*)collider);
    }

    if (this->hasEffect(Effect::P_BALL_ACCELERATE)) {
        collider->onEvent(EventArgs("accelerate"));
    }

    if (this->hasEffect(Effect::P_PIPE_ENLARGE)) {
        game->ePipe->setWidth(game->ePipe->getWidth() * 1.1f);
    }

    if (this->hasEffect(Effect::P_PIPE_SHORTEN)) {
        game->ePipe->setWidth(game->ePipe->getWidth() * 0.9f);
    }
}

sf::RectangleShape& EBlock::getColliderbox() {
    return this->collider;
}

bool EBlock::hasEffect(Effect effect) {
    for (Effect e : this->effects) {
        if (e == effect) {
            return true;
        }
    }
    return false;
}

void EBlock::addEffect(Effect effect) {
    if (this->hasEffect(effect)) return;
    this->effects.push_back(effect);
}

void EBlock::removeEffect(Effect effect) {
    for (int i = 0; i < this->effects.size(); i++) {
        if (this->effects[i] == effect) {
            this->effects.erase(this->effects.begin() + i);
        }
    }
}

void EBlock::setText(const std::string& text, const sf::Font font) {
    this->hasText = true;
    auto mySize = this->collider.getSize();
    this->text = sf::Text(text, font);
    this->text.setCharacterSize(mySize.y - 6);
    auto textSize = this->text.getLocalBounds();
    this->text.setPosition(ceilf(this->posX + (mySize.x / 2.0f) - (textSize.left + textSize.width / 2.0f)), ceilf(this->posY + (mySize.y / 2.0f) - (textSize.top + textSize.height / 2.0f)));
}
