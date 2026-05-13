#include "Door.hpp"
#include <string>

namespace
{
    sf::Texture *getPlayerOneDoorTexture()
    {
        static sf::Texture texture;
        static bool attemptedLoad = false;

        if (!attemptedLoad)
        {
            texture.loadFromFile(std::string(GAME_ASSET_DIR) + "/textures/"); // bus pakeista
            texture.setRepeated(true);
            attemptedLoad = true;
        }

        if (texture.getSize().x == 0 || texture.getSize().y == 0)
            return nullptr;

        return &texture;
    }

    sf::Texture *getPlayerTwoDoorTexture()
    {
        static sf::Texture texture;
        static bool attemptedLoad = false;

        if (!attemptedLoad)
        {
            texture.loadFromFile(std::string(GAME_ASSET_DIR) + "/textures/"); // bus pakeista
            texture.setRepeated(true);
            attemptedLoad = true;
        }

        if (texture.getSize().x == 0 || texture.getSize().y == 0)
            return nullptr;

        return &texture;
    }

}

Door::Door(float x, float y, float width, float height, DoorType type)
{
    this->type = type;

    door.setSize(sf::Vector2f(width, height));
    door.setPosition(x, y);
    door.setTextureRect(sf::IntRect(0, 0, static_cast<int>(width), static_cast<int>(height)));
    door.setFillColor(sf::Color::White);

    if (type == DoorType::playerOneDoor)
    {
        if (sf::Texture *texture = getPlayerOneDoorTexture())
            door.setTexture(texture);
        else
            door.setFillColor(sf::Color::Red);
    }
    else if (type == DoorType::playerTwoDoor)
    {
        if (sf::Texture *texture = getPlayerTwoDoorTexture())
            door.setTexture(texture);
        else
            door.setFillColor(sf::Color::Blue);
    }
}

void Door::draw(sf::RenderWindow &window)
{
    window.draw(door);
}

sf::FloatRect Door::getBounds()
{
    return door.getGlobalBounds();
}

DoorType Door::getType()
{
    return type;
}

bool Door::isOpen() const { return opened; }
void Door::open() { opened = true; }
