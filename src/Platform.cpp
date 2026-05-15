#include "Platform.hpp"

Platform::Platform(float x, float y, float width, float height, PlatformType type)
: type(type)
{
    shape.setSize(sf::Vector2f(width, height));
    shape.setPosition(x, y);

    if (type == PlatformType::movingVertically)
        applyTexture("platform.png");
    else
        applyTexture("tile.png");

    startY = y;
}

void Platform::update(float dt)
{
    if (type == PlatformType::movingVertically)
    {
        shape.move(0.f, direction * speed * dt);
        float currentY = shape.getPosition().y;

        if (currentY > startY + moveRange)
            direction = -1;
        if (currentY < startY - moveRange)
            direction = 1;
    }
}

PlatformType Platform::getType() { return type; }