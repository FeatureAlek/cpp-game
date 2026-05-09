#pragma once
#include <SFML/Graphics.hpp>

enum class GemType
{
    redGem,
    blueGem
};

class Gem
{
public:
    Gem(float x, float y, float width, float height, GemType);
    void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds();
    GemType getType();
    
    bool isCollected() const;
    void collect();

private:
    sf::RectangleShape gem;
    GemType type;
    bool collected = false;
};