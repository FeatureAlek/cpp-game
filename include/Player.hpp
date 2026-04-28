#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_set>
#include "Hazard.hpp"

class Player
{
public:
    Player(float x, float y, sf::Color color);

    void respawn();
    bool canTouch(HazardType type) const;
    void addAllowed(HazardType type);

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
    // setters
    void setPositionX(float x);
    void setPositionY(float y);
    
    void setVelocityX(float v);
    void setVelocityY(float v);
    void setOnGround(bool v);

private:

    float spawnX;
    float spawnY;

    float speed = 200.f;
    float velocityY = 0.f;
    float velocityX = 0.f; 

    float gravity = 800.f; // downward acceleration
    bool onGround = false;

    sf::RectangleShape shape;

    std::unordered_set<HazardType> allowedHazards;

};