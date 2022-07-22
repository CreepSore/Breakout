#include "EBall.hpp"
#include "Breakout.hpp"
#define M_PI 3.141f

class Breakout;

EBall::EBall() {
    this->updateColliderBox();
}

void EBall::render(float delta, sf::RenderWindow& window)
{
    float iX;
    float iY;
    this->interpolate(&iX, &iY, 1, 1);

    sf::CircleShape body = sf::CircleShape(this->radius);
    body.setPosition(iX - (this->radius / 2), iY - (this->radius / 2));

    if (this->isSticky) {
        sf::VertexArray vertex = sf::VertexArray(sf::LineStrip);
        vertex.append(sf::Vertex(sf::Vector2f(iX + (this->radius / 2), iY + (this->radius / 2)), sf::Color(255, 0, 0, 255)));
        for (int i = 0; i < 25; i++) {
            float interpolatedX = 0;
            float interpolatedY = 0;
            this->interpolate(&interpolatedX, &interpolatedY, i + 1, 1.0f, 10.0f);
            vertex.append(sf::Vertex(sf::Vector2f(interpolatedX + (this->radius / 2), interpolatedY + (this->radius / 2)), sf::Color(255, 0, 0, 255)));
        }

        window.draw(vertex);
    }
    window.draw(body);
}

void EBall::tick()
{
    CollisionResult result = {};
    this->precomputeTick(&this->posX, &this->posY, &this->direction, &result);
    if (result.hasCollided) {

    }
}

void EBall::precomputeTick(float* cX, float* cY, float* cDir, CollisionResult* collision)
{
    Breakout* game = Breakout::getInstance();
    EPipe ePipe = game->ePipe;

    this->posX += sinf(this->direction * (M_PI / 180.0f)) * this->speed;
    this->posY += (-(cosf(this->direction * (M_PI / 180.0f)))) * this->speed;

    CollisionResult cRes = this->checkCollisionWith(&game->ePipe);
    if (cRes.hasCollided) {
        float deltaBallPipe = this->posX - this->posX + this->getRadius();
        this->direction = ((deltaBallPipe / (this->collider.width + this->getRadius())) * 176) - 88;
        collision->entity = this;
        collision->target = &game->ePipe;
        collision->hasCollided = true;
        collision->type = PIPE;
        return;
    }

    if (this->isSticky) {
        if (this->posX < ePipe.posX - this->getRadius()) this->posX = ePipe.posX - this->getRadius();
        if (this->posX > ePipe.posX + ePipe.collider.width) this->posX = ePipe.posX + ePipe.collider.width;
        this->posY = ePipe.posY - this->getRadius() - 10;

        float deltaBallPipe = this->posX - game->ePipe.posX + this->getRadius();
        this->direction = ((deltaBallPipe / (ePipe.collider.width + this->getRadius())) * 176) - 88;
    }

    for (EBlock* block : game->blocks) {
        if (block->destroyed) continue;

        CollisionResult blockCollision = this->checkCollisionWith(block);
        if (blockCollision.hasCollided) {
            block->onCollision();
            this->onCollision(blockCollision);
            return block;
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

        CollisionResult cRes = IEntity::checkCollisionWith(iX, iY, this->collider, game->ePipe.posX, game->ePipe.posY, game->ePipe.collider);
        if (cRes.hasCollided) {
            float deltaBallPipe = iX - game->ePipe.posX + this->getRadius();
            direction = ((deltaBallPipe / (this->collider.width + this->getRadius())) * 176) - 88;
        }
    }
    *outX = iX;
    *outY = iY;
}

float EBall::getDirectionChangeOnCollision(CollisionType collisionType, float baseDirection)
{
    float result = baseDirection;
    if (collisionType == RIGHT || collisionType == LEFT) {
        result = -result;
    }

    if (collisionType == TOP || collisionType == 10 || collisionType == BOTTOM) {
        result = -result + 180;
    }

    while (result > 360.0f) result -= 360;
    while (result < 0.0f) result += 360;

    return result;
}

void EBall::updateColliderBox()
{
    this->collider = BoundingBox(-(radius / 2), -(radius / 2), radius, radius);
}
