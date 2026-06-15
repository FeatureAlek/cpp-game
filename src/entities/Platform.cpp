#include "Platform.hpp"

Platform::Platform(float x, float y, float width, float height, PlatformType type)
    : type(type)
{
    shape.setSize(sf::Vector2f(width, height));
    shape.setPosition(x, y);

    if (type == PlatformType::movingVertically)
        applyTexture("platform.png");
    else if (type == PlatformType::buttonControlled)
        applyTexture("platform.png");  // this could be different texture for moving platform!
    else
        applyTexture("tile.png");

    startY = y;
}

void Platform::setActive(bool active)
{
    this->active = active;
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
    else if (type == PlatformType::buttonControlled)
    {
        float currentY = shape.getPosition().y;

        if (active)
        {
            // moves down until the limit
            if (currentY < startY + Config::PLATFORM_MOVE_RANGE)
                shape.move(0.f, Config::PLATFORM_SPEED * dt);
        }
        else
        {
            // get back to its starting position
            if (currentY > startY)
                shape.move(0.f, -Config::PLATFORM_SPEED * dt);
        }
    }
}

PlatformType Platform::getType() const { return type; }