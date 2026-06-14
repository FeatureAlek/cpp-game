#include "Gem.hpp"

Gem::Gem(float x, float y, float width, float height, GemType type)
: type(type)
{
    shape.setSize(sf::Vector2f(width, height));
    shape.setPosition(x, y);

    if (type == GemType::redGem)
        applyTexture("firegem.png");
    else
        applyTexture("bluegem.png");
}

GemType Gem::getType()        { return type; }
bool Gem::isCollected() const { return collected; }
void Gem::collect()           { collected = true; }