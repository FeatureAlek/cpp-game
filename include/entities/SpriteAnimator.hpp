#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class SpriteAnimator
{
public:
    SpriteAnimator() = default;

    bool load(const std::string& spriteFile);
    void update(float dt, float currentX, float previousX);
    void draw(sf::RenderWindow& window);
    void syncPosition(sf::Vector2f position, sf::Vector2f hitboxSize);
    void setFacingRight(bool right);
    void resetToIdle();

    bool isLoaded() const { return hasSprite; }

private:
    sf::Texture spriteSheet;
    sf::Sprite sprite;
    bool hasSprite = false;
    bool facingRight = true;
    int animationIndex = 0;
    float animationTimer = 0.f;

    void updateTextureRect(int frame = -1);
    void syncVisualPosition(sf::Vector2f position, sf::Vector2f hitboxSize);
    void createSpriteSheet(const std::string& spriteFile);
};