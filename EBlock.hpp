#pragma once
#include "./IEntity.hpp"
#include "./Effect.hpp"

class EBlock : public IEntity {
public:
    EBlock(float posX, float posY, float width, float height);
    
    virtual void render(float delta, sf::RenderWindow& window) override;
    virtual void tick() override;
    virtual sf::RectangleShape getColliderbox() override;
    void onCollision(IEntity* collider);
    bool hasEffect(Effect effect);
    void addEffect(Effect effect);
    void removeEffect(Effect effect);

    sf::RectangleShape collider;

    bool destroyed = false;
private:
    std::vector<Effect> effects;
};
