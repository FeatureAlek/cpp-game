#include "Hazard.hpp"
#include <string>

namespace
{
    sf::Texture *getOrangeRiverTexture()
    {
        static sf::Texture texture;
        static bool attemptedLoad = false;

        if (!attemptedLoad)
        {
            texture.loadFromFile(std::string(GAME_ASSET_DIR) + "/textures/orangeriver.jpg");
            texture.setRepeated(true);
            attemptedLoad = true;
        }

        if (texture.getSize().x == 0 || texture.getSize().y == 0)
            return nullptr;

        return &texture;
    }

    sf::Texture *getBlueRiverTexture()
    {
        static sf::Texture texture;
        static bool attemptedLoad = false;

        if (!attemptedLoad)
        {
            texture.loadFromFile(std::string(GAME_ASSET_DIR) + "/textures/blueriver.jpg");
            texture.setRepeated(true);
            attemptedLoad = true;
        }

        if (texture.getSize().x == 0 || texture.getSize().y == 0)
            return nullptr;

        return &texture;
    }

    sf::Texture *getNeutralRiverTexture()
    {
        static sf::Texture texture;
        static bool attemptedLoad = false;

        if (!attemptedLoad)
        {
            texture.loadFromFile(std::string(GAME_ASSET_DIR) + "/textures/neutralriver.png");
            texture.setRepeated(true);
            attemptedLoad = true;
        }

        if (texture.getSize().x == 0 || texture.getSize().y == 0)
            return nullptr;

        return &texture;
    }
}

Hazard::Hazard(float x, float y, float width, float height, HazardType type)
{
    this->type = type;

    hazard.setSize(sf::Vector2f(width, height));
    hazard.setPosition(x, y);
    hazard.setTextureRect(sf::IntRect(0, 0, static_cast<int>(width), static_cast<int>(height)));
    hazard.setFillColor(sf::Color::White);

    if (type == HazardType::playerOneRiver)
    {
        if (sf::Texture *texture = getOrangeRiverTexture())
            hazard.setTexture(texture);
        else
            hazard.setFillColor(sf::Color::Red);
    }
    else if (type == HazardType::playerTwoRiver)
    {
        if (sf::Texture *texture = getBlueRiverTexture())
            hazard.setTexture(texture);
        else
            hazard.setFillColor(sf::Color::Blue);
    }
    else
    {
        if (sf::Texture *texture = getNeutralRiverTexture())
            hazard.setTexture(texture);
        else
            hazard.setFillColor(sf::Color::Green);
    }
}

void Hazard::draw(sf::RenderWindow &window)
{
    window.draw(hazard);
}

sf::FloatRect Hazard::getBounds()
{
    return hazard.getGlobalBounds();
}

HazardType Hazard::getType()
{
    return type;
}
