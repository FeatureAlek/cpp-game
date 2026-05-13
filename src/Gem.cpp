#include "Gem.hpp"
#include <string>

namespace
{
    sf::Texture *getRedGemTexture()
    {
        static sf::Texture texture;
        static bool attemptedLoad = false;

        if (!attemptedLoad)
        {
            texture.loadFromFile(std::string(GAME_ASSET_DIR) + "/textures/firegem.png");
            texture.setRepeated(true);
            attemptedLoad = true;
        }

        if (texture.getSize().x == 0 || texture.getSize().y == 0)
            return nullptr;

        return &texture;
    }

    sf::Texture *getBlueGemTexture()
    {
        static sf::Texture texture;
        static bool attemptedLoad = false;

        if (!attemptedLoad)
        {
            texture.loadFromFile(std::string(GAME_ASSET_DIR) + "/textures/bluegem.png");
            texture.setRepeated(true);
            attemptedLoad = true;
        }

        if (texture.getSize().x == 0 || texture.getSize().y == 0)
            return nullptr;

        return &texture;
    }
}

Gem::Gem(float x, float y, float width, float height, GemType type)
{
    this->type = type;
    
    gem.setSize(sf::Vector2f(width, height));
    gem.setPosition(x, y);
    gem.setTextureRect(sf::IntRect(0, 0, static_cast<int>(width), static_cast<int>(height)));
    gem.setFillColor(sf::Color::White);

    if (type == GemType::redGem)
    {
        if (sf::Texture *texture = getRedGemTexture())
            gem.setTexture(texture);
        else
            gem.setFillColor(sf::Color::Red);
    }
    else
    {
        if (sf::Texture *texture = getBlueGemTexture())
            gem.setTexture(texture);
        else
            gem.setFillColor(sf::Color::Blue);
    }
}

void Gem::draw(sf::RenderWindow &window)
{
    window.draw(gem);
}

sf::FloatRect Gem::getBounds()
{
    return gem.getGlobalBounds();
}

GemType Gem::getType()
{
    return type;
}

bool Gem::isCollected() const 
{ 
    return collected; 
}

void Gem::collect()
{ 
    collected = true; 
}