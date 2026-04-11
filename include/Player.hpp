#pragma once
#include <SFML/Graphics.hpp>

class Player
{
public:
    Player(float x, float y, sf::Color color);

    // movement
    void moveLeft(float dt);
    void moveRight(float dt);
    void jump();

    // rendering
    void draw(sf::RenderWindow& window);
    
    // collision
    void applyGravity(float dt);
    bool isOnGround(const sf::RectangleShape& ground);
    void stopFalling(const sf::RectangleShape& ground);
    
    sf::FloatRect getBounds();
    void setPositionX(float x);

private:

    float speed = 200.f;
    float velocityY = 0.f; // speed downwards
    float gravity = 800.f; // downward acceleration
    bool onGround = false;

    sf::RectangleShape shape;

};