#include "EBall.hpp"
#include "Breakout.hpp"
#define M_PI 3.141f

class Breakout;

EBall::EBall() {
    this->collider = sf::RectangleShape();
    this->body = sf::CircleShape(this->radius);
    this->updateColliderBox();
}

void EBall::render(float delta, sf::RenderWindow& window)
{
    window.draw(body);
}

void EBall::tick()
{
    Breakout* game = Breakout::getInstance();

    CollisionResult result = {};
    this->precomputeTick(&this->posX, &this->posY, &this->direction, &result);
    body.setPosition(this->posX - (this->radius / 2), this->posY - (this->radius / 2));
}

void EBall::precomputeTick(float* cX, float* cY, float* cDir, CollisionResult* collision)
{
    Breakout* game = Breakout::getInstance();
    auto sizeBall = this->getColliderbox().getSize();
    EPipe* ePipe = game->ePipe;
    auto ePipeSize = ePipe->collider.getSize();

    if (this->isSticky) {
        if (this->posX < ePipe->posX - this->radius) this->posX = ePipe->posX - this->radius;
        if (this->posX > ePipe->posX + ePipeSize.x) this->posX = ePipe->posX + ePipeSize.x;
        this->posY = ePipe->posY - (this->radius * 2);

        float deltaBallPipe = this->posX - ePipe->posX + this->radius;
        this->direction = ((deltaBallPipe / (ePipeSize.x + this->radius)) * 176) - 88;
        this->updateColliderBox();
        return;
    }

    float steps = 10;
    for (int i = 0; i < steps; i++) {
        this->posX += sinf(this->direction * (M_PI / 180.0f)) * (this->speed * (1 / steps));
        this->posY += (-(cosf(this->direction * (M_PI / 180.0f)))) * (this->speed * (1 / steps));
        this->updateColliderBox();

        if (this->posY > BO_ARENA_HEIGHT / 2) {
            CollisionResult cRes = this->checkCollisionWith(game->ePipe);
            if (cRes.hasCollided) {
                this->posY = cRes.intersection.top - (this->radius * 2);
                float deltaBallPipe = this->posX - ePipe->posX + this->radius;
                this->direction = ((deltaBallPipe / (ePipe->getColliderbox().getSize().x + this->radius)) * 176) - 88;
                this->posX += sinf(this->direction * (M_PI / 180.0f)) * (this->speed * (1 / steps));
                this->posY += (-(cosf(this->direction * (M_PI / 180.0f)))) * (this->speed * (1 / steps));
                return;
            }
        }

        for (EBlock* block : game->blocks) {
            if (block->destroyed) continue;
            CollisionResult blockCollision = this->checkCollisionWith(block);
            if (blockCollision.hasCollided) {
                auto sizeBlock = block->getColliderbox().getSize();
                if (blockCollision.intersection.width > blockCollision.intersection.height) {
                    if (this->posY + sizeBall.y > block->posY) {
                        blockCollision.type = CollisionType::BOTTOM;
                    }

                    if (this->posY < block->posY + sizeBlock.y) {
                        blockCollision.type = CollisionType::TOP;
                    }
                }
                else {
                    if (this->posX < block->posX + sizeBlock.x) {
                        blockCollision.type = CollisionType::RIGHT;
                    }

                    if (this->posX + sizeBall.x > block->posX) {
                        blockCollision.type = CollisionType::LEFT;
                    }
                }

                this->onCollision(blockCollision);
                block->onCollision(this);

                return;
            }
        }
    }
}

int EBall::getRadius()
{
    return this->radius;
}

void EBall::setRadius(float radius)
{
    this->radius = radius;
    this->updateColliderBox();
    this->body.setRadius(this->radius);

    return;
}

void EBall::shoot(float speed)
{
    if (speed = -1) {
        speed = BO_DEFAULT_BALL_SPEED;
    }
    this->speed = speed;
}

void EBall::onCollision(CollisionResult result)
{
    this->direction = this->getDirectionChangeOnCollision(result.type, this->direction);
    this->posX += sinf(this->direction * (M_PI / 180.0f)) * (this->speed);
    this->posY += (-(cosf(this->direction * (M_PI / 180.0f)))) * (this->speed);
}

void EBall::interpolate(float* outX, float* outY, float ticks, float tickstep, float speed)
{
    if (speed == -1) speed = this->speed;
    Breakout* game = Breakout::getInstance();

    float iX = this->posX;
    float iY = this->posY;
    float direction = this->direction;
    for (float i = 0; i < ticks; i += tickstep) {
        iX += sinf(direction * (M_PI / 180.0f)) * speed * tickstep;
        iY += (-(cosf(direction * (M_PI / 180.0f)))) * speed * tickstep;

        for (EBlock* block : game->blocks) {
            if (block->destroyed) continue;

            CollisionResult blockCollision = IEntity::checkCollisionWith(iX, iY, this->collider, block->posX, block->posY, block->collider);
            if (blockCollision.hasCollided) {
                direction = this->getDirectionChangeOnCollision(blockCollision.type, direction);
            }
        }

        CollisionResult cRes = IEntity::checkCollisionWith(iX, iY, this->collider, game->ePipe->posX, game->ePipe->posY, game->ePipe->collider);
        if (cRes.hasCollided) {
            float deltaBallPipe = iX - game->ePipe->posX + this->getRadius();
            direction = ((deltaBallPipe / (this->collider.getSize().x + this->getRadius())) * 176) - 88;
        }
    }
    *outX = iX;
    *outY = iY;
}

float EBall::getDirectionChangeOnCollision(CollisionType collisionType, float baseDirection)
{
    float result = baseDirection;
    if (collisionType == CollisionType::RIGHT || collisionType == CollisionType::LEFT) {
        result = -result;
    }

    if (collisionType == CollisionType::TOP || (int)collisionType == 10 || collisionType == CollisionType::BOTTOM) {
        result = -result + 180;
    }

    while (result > 360.0f) result -= 360;
    while (result < 0.0f) result += 360;

    return result;
}

void EBall::updateColliderBox()
{
    sf::Vector2f vec = sf::Vector2f(this->posX - (radius / 2), this->posY - (radius / 2));
    this->collider.setPosition(vec);
}

sf::RectangleShape& EBall::getColliderbox() {
    return this->collider;
}

void EBall::onEvent(EventArgs args) {
    if (args.eventName == "accelerate") {
        this->speed *= 1.1;
    }
}
