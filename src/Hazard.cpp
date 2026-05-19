#include "Hazard.hpp"

Hazard::Hazard(float x, float y, float width, float height, HazardType type)
: type(type)
{
    shape.setSize(sf::Vector2f(width, height));
    shape.setPosition(x, y);

    if (type == HazardType::playerOneRiver)
        applyTexture("orangeriver.png");
    else if (type == HazardType::playerTwoRiver)
        applyTexture("blueriver.png");
    else
        applyTexture("neutralriver.png");
}

HazardType Hazard::getType() { return type; }
