#pragma once
#include "./IEntity.hpp"
#define BO_DEFAULT_BALL_SPEED 10.0f;

class EBall : public IEntity {
public:
    EBall();

    virtual void render(float delta, sf::RenderWindow& window) override;
    virtual void tick() override;
    virtual sf::RectangleShape& getColliderbox() override;
    virtual void onEvent(EventArgs args) override;
    void precomputeTick(float* cX, float* cY, float* cDir, CollisionResult* collision);

    sf::RectangleShape collider;
    sf::CircleShape body;

    int getRadius();
    void setRadius(float radius);
    void shoot(float speed = -1);
    void onCollision(CollisionResult type);
    void interpolate(float* outX, float* outY, float ticks, float tickstep = 0.1, float speed = -1);
    float getDirectionChangeOnCollision(CollisionType collisionType, float baseDirection);

    float direction = 0;
    float speed = 0;
    bool isSticky = false;
private:
    int radius = 5;
    void updateColliderBox();
};
