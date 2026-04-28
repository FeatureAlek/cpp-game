#include "Hazard.hpp"

Hazard::Hazard(float x, float y, float width, float height, HazardType type)
{
    this->type = type;

    hazard.setSize(sf::Vector2f(width, height));
    hazard.setPosition(x,y);
    
    if(type == HazardType::playerOneRiver)
        hazard.setFillColor(sf::Color::Red);
    else if(type == HazardType::playerTwoRiver)
        hazard.setFillColor(sf::Color::Blue);
    else
        hazard.setFillColor(sf::Color::Green);
}

void Hazard::draw(sf::RenderWindow& window)
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