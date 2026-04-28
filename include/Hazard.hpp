#pragma once
#include <SFML/Graphics.hpp>

enum class HazardType
{
    playerOneRiver, // color red
    playerTwoRiver, // color blue
    generalRiver // color green
};

class Hazard
{
public:
    Hazard(float x, float y, float width, float height, HazardType type);
    void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds();
    HazardType getType();

private:
    sf::RectangleShape hazard;
    HazardType type;
};