#pragma once
#include <SFML/Graphics.hpp>

enum class PlatformType
{
    movingVertically,
    notMoving
};

class Platform
{
public:
    Platform(float x, float y, float width, float height, PlatformType);
    
    sf::FloatRect getBounds();
    PlatformType getType();
    
    void draw(sf::RenderWindow& window);
    void update(float dt);

private:
    float speed = 60.f;

    float startY = 0.f;
    float moveRange = 50.f;
    int direction = 1;

    sf::RectangleShape platform;
    PlatformType type;
};