#include "Door.hpp"

namespace
{
constexpr float kDoorScale = 2.f;
}

Door::Door(float x, float y, float width, float height, DoorType type)
: type(type)
{
    shape.setSize(sf::Vector2f(width, height));
    shape.setScale(kDoorScale, kDoorScale);
    shape.setPosition(
        x - (width * (kDoorScale - 1.f) * 0.5f),
        y - (height * (kDoorScale - 1.f)));


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