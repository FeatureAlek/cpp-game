#pragma once
#include <SFML/Graphics.hpp>

class Player
{
public:
    Player(float x, float y, sf::Color color);


    void moveLeft(float dt);
    void moveRight(float dt);
    void moveUp(float dt);

    void draw(sf::RenderWindow& window);

private:
    sf::RectangleShape shape;
    float speed = 200.f;

};