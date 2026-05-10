#pragma once
#include <SFML/Graphics.hpp>

enum class DoorType
{
    playerOneDoor,
    playerTwoDoor
};

class Door
{
public:
    Door(float x, float y, float width, float height, DoorType type);
    void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds();
    DoorType getType();
    
    bool isOpen() const;
    void open();

private:
    sf::RectangleShape door;
    DoorType type;

    bool opened = false;
};