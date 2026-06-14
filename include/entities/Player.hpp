#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_set>
#include "Hazard.hpp"
#include "Gem.hpp"
#include "Door.hpp"
#include "Config.hpp"
#include "SpriteAnimator.hpp"

class Player
{
public:
    Player(float x, float y, sf::Color color, const std::string& spriteFile = "");

    // hazards
    bool canTouch(HazardType type) const;
    void addAllowed(HazardType type);

    // gems
    bool canTouch(GemType) const;
    void addAllowed(GemType type);
    void addGem();
    int getGemCount() const;
    void resetGemCount();

    // doors
    bool canTouch(DoorType) const;
    void addAllowed(DoorType type);

    // movement
    void moveLeft(float dt);
    void moveRight(float dt);
    void jump();
    void respawn();

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
    int gemCount = 0;
    float spawnX = 0.f;
    float spawnY = 0.f;
    float velocityY = 0.f;
    float velocityX = 0.f;
    float speed    = Config::PLAYER_SPEED;
    float gravity  = Config::PLAYER_GRAVITY;
    float previousX = 0.f;
    bool onGround = false;

    sf::RectangleShape shape;
    SpriteAnimator animator;

    std::unordered_set<HazardType> allowedHazards;
    std::unordered_set<GemType>   allowedGems;
    std::unordered_set<DoorType>  allowedDoors;
};