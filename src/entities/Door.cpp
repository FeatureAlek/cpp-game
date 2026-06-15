#include "Door.hpp"
#include "Config.hpp"

Door::Door(float x, float y, float width, float height, DoorType type)
: type(type)
{
    shape.setSize(sf::Vector2f(width, height));
    shape.setScale(Config::DOOR_SCALE, Config::DOOR_SCALE);
    shape.setPosition(
        x - (width * (Config::DOOR_SCALE - 1.f) * 0.5f),
        y - (height * (Config::DOOR_SCALE - 1.f)));


    if (type == DoorType::playerOneDoor)
    {
        shape.setFillColor(sf::Color::Red);
        applyTexture("door_red.png");
    }
    else
    {
        shape.setFillColor(sf::Color::Blue);
        applyTexture("door_blue.png");
    }
}

DoorType Door::getType()  { return type; }
bool Door::isOpen() const { return opened; }
void Door::open()         { opened = true; }