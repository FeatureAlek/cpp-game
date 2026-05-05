#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_set>
#include "Hazard.hpp"

class Player
{
public:
    Player(float x, float y, sf::Color color, const std::string& spriteFile = "");

    void respawn();
    bool canTouch(HazardType type) const;
    void addAllowed(HazardType type);

    // movement
    void moveLeft(float dt);
    void moveRight(float dt);
    void jump();

    // rendering
    void draw(sf::RenderWindow& window);
    void updateAnimation(float dt);
    
    // collision
    void applyGravity(float dt);
    bool isOnGround(const sf::RectangleShape& ground);
    void stopFalling(const sf::RectangleShape& ground);
    
    sf::FloatRect getBounds();
    float getVelocityY() const;
    // setters
    void setPositionX(float x);
    void setPositionY(float y);
    
    void setVelocityX(float v);
    void setVelocityY(float v);
    void setOnGround(bool v);

    void setSpawnPoint(float x, float y);
private:
    void syncVisualPosition();
    void updateTextureRect(int frame = -1);
    void createSpriteSheet(const std::string& spriteFile);

    float spawnX;
    float spawnY;

    float speed = 200.f;
    float velocityY = 0.f;
    float velocityX = 0.f; 

    float gravity = 800.f; // downward acceleration
    bool onGround = false;
    bool hasSprite = false;
    bool facingRight = true;

    float animationTimer = 0.f;
    float previousX = 0.f;
    std::size_t animationIndex = 0;

    sf::RectangleShape shape;
    sf::Texture spriteSheet;
    sf::Sprite sprite;

    std::unordered_set<HazardType> allowedHazards;

};