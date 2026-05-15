#include "Door.hpp"

Door::Door(float x, float y, float width, float height, DoorType type)
: type(type)
{
    shape.setSize(sf::Vector2f(width, height));
    shape.setPosition(x, y);

    if (type == DoorType::playerOneDoor)
    {
        shape.setFillColor(sf::Color::Red); // fallback
        applyTexture("door_red.png"); // <- pakeisti
    }
    else
    {
        shape.setFillColor(sf::Color::Blue); // fallback
        applyTexture("door_blue.png"); // <- pakeisti
    }
}

DoorType Door::getType()  { return type; }
bool Door::isOpen() const { return opened; }
void Door::open()         { opened = true; }