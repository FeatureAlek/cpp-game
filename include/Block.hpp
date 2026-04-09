#pragma once
#include <SFML/Graphics.hpp>

class Block
{
private:
    sf::RectangleShape shape;

public:
    Block(float x, float y);

    void draw(sf::RenderWindow& window);
};