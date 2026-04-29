#include "Platform.hpp"

Platform::Platform(float x, float y, float width, float height, PlatformType type)
{
    this->type = type;

    platform.setSize(sf::Vector2f(width, height));
    platform.setPosition(x,y);
    platform.setFillColor(sf::Color(100, 70, 40));

    startY = y;
}

void Platform::update(float dt)
{
    if(type == PlatformType::movingVertically)
    {
        platform.move(0.f, direction * speed * dt);

        float currentY = platform.getPosition().y;

        if(currentY > startY + moveRange)
            direction = -1;

        if(currentY < startY - moveRange)
            direction = 1;
    }
}

sf::FloatRect Platform::getBounds()
{
    return platform.getGlobalBounds();
}

void Platform::draw(sf::RenderWindow& window)
{
    window.draw(platform);
}

PlatformType Platform::getType()
{
    return type;
}