#include "Platform.hpp"
#include <string>

namespace
{
sf::Texture* getTileTexture()
{
    static sf::Texture texture;
    static bool attemptedLoad = false;

    if (!attemptedLoad)
    {
        texture.loadFromFile(std::string(GAME_ASSET_DIR) + "/textures/tile.png");
        texture.setRepeated(true);
        attemptedLoad = true;
    }

    if (texture.getSize().x == 0 || texture.getSize().y == 0)
        return nullptr;

    return &texture;
}

sf::Texture* getPlatformTexture()
{
    static sf::Texture texture;
    static bool attemptedLoad = false;

    if (!attemptedLoad)
    {
        texture.loadFromFile(std::string(GAME_ASSET_DIR) + "/textures/platform.png");
        texture.setRepeated(true);
        attemptedLoad = true;
    }

    if (texture.getSize().x == 0 || texture.getSize().y == 0)
        return nullptr;

    return &texture;
}
}

Platform::Platform(float x, float y, float width, float height, PlatformType type)
{
    this->type = type;

    platform.setSize(sf::Vector2f(width, height));
    platform.setPosition(x,y);
    sf::Texture* texture = nullptr;
    if (type == PlatformType::movingVertically)
        texture = getPlatformTexture();
    else
        texture = getTileTexture();

    if (texture)
    {
        platform.setTexture(texture);
        platform.setTextureRect(sf::IntRect(0, 0, static_cast<int>(width), static_cast<int>(height)));
        platform.setFillColor(sf::Color::White);
    }
    else
    {
        platform.setFillColor(sf::Color(100, 70, 40));
    }

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
