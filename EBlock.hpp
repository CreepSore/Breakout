#pragma once
#include "./IEntity.hpp"
#include "./Effect.hpp"

class EBlock : public IEntity {
public:
    EBlock(float posX, float posY, float width, float height);
    
    virtual void render(float delta, sf::RenderWindow& window) override;
    virtual void tick() override;
    virtual sf::RectangleShape& getColliderbox() override;
    void onCollision(IEntity* collider);
    bool hasEffect(Effect effect);
    void addEffect(Effect effect);
    void removeEffect(Effect effect);
    void setText(const std::string& text, const sf::Font font);

    sf::RectangleShape body;
    sf::Text text;
    sf::RectangleShape collider;
    sf::Color color;
    sf::Color textColor;

    bool destroyed = false;
private:
    bool hasText = false;
    std::vector<Effect> effects;
};
