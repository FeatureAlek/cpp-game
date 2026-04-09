#include "Block.hpp"

Block::Block(float x, float y)
{
    shape.setSize(sf::Vector2f(100.f,100.f));
    shape.setFillColor(sf::Color::Green);
    shape.setPosition(x,y);
}

void Block::draw(sf::RenderWindow& window)
{
    window.draw(shape);
}