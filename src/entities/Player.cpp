#include "Player.hpp"
#include <cmath>

Player::Player(float x, float y, sf::Color color, const std::string &spriteFile)
{
    float hitboxWidth = Config::PLAYER_HITBOX;
    float hitboxHeight = Config::PLAYER_HITBOX;
    if (!spriteFile.empty())
    {
        hitboxWidth *= Config::PLAYER_HITBOX_WIDTH_SCALE;
        hitboxHeight *= Config::PLAYER_HITBOX_HEIGHT_SCALE;
    }

    shape.setSize(sf::Vector2f(hitboxWidth, hitboxHeight));
    shape.setFillColor(color);
    shape.setPosition(x, y);

    // save spawn position
    spawnX = x;
    spawnY = y;
    previousX = x;

    if (!spriteFile.empty())
        animator.load(spriteFile);
}

void Player::draw(sf::RenderWindow &window)
{
    if (animator.isLoaded())
        animator.draw(window);
    else
        window.draw(shape);
}

void Player::moveLeft(float dt)
{
    animator.setFacingRight(false);
    shape.move(-speed * dt, 0.f);
    animator.syncPosition(shape.getPosition(), shape.getSize());
}

void Player::moveRight(float dt)
{
    animator.setFacingRight(true);
    shape.move(speed * dt, 0.f);
    animator.syncPosition(shape.getPosition(), shape.getSize());
}

void Player::updateAnimation(float dt)
{
    animator.update(dt, shape.getPosition().x, previousX);
    animator.syncPosition(shape.getPosition(), shape.getSize());
    previousX = shape.getPosition().x;
}

void Player::applyGravity(float dt)
{
    velocityY += gravity * dt;
    shape.move(0.f, velocityY * dt);
    animator.syncPosition(shape.getPosition(), shape.getSize());
}

bool Player::isOnGround(const sf::RectangleShape &ground)
{
    const sf::FloatRect playerBounds = shape.getGlobalBounds();
    const sf::FloatRect groundBounds = ground.getGlobalBounds();

    const float playerBottom = playerBounds.top + playerBounds.height;
    const float playerRight = playerBounds.left + playerBounds.width;
    const float groundRight = groundBounds.left + groundBounds.width;

    const bool overlapsHorizontally =
        playerRight > groundBounds.left && playerBounds.left < groundRight;

    return overlapsHorizontally && playerBottom >= groundBounds.top;
}

void Player::stopFalling(const sf::RectangleShape &ground)
{
    velocityY = 0.f;
    onGround = true;
    float groundTop = ground.getPosition().y;
    float playerHeight = shape.getSize().y;
    shape.setPosition(shape.getPosition().x, groundTop - playerHeight);
    animator.syncPosition(shape.getPosition(), shape.getSize());
}

void Player::jump()
{
    if (onGround)
    {
        velocityY = Config::PLAYER_JUMP;
        onGround = false;
    }
}

sf::FloatRect Player::getBounds()
{
    return shape.getGlobalBounds();
}

float Player::getVelocityY() const
{
    return velocityY;
}
// setters

void Player::setPositionX(float x)
{
    shape.setPosition(x, shape.getPosition().y);
    animator.syncPosition(shape.getPosition(), shape.getSize());
}

void Player::setPositionY(float y)
{
    shape.setPosition(shape.getPosition().x, y);
    animator.syncPosition(shape.getPosition(), shape.getSize());
}

void Player::setVelocityX(float v)
{
    velocityX = v;
}

void Player::setVelocityY(float v)
{
    velocityY = v;
}

void Player::setOnGround(bool v)
{
    onGround = v;
}

// Hazards
bool Player::canTouch(HazardType type) const
{
    return allowedHazards.find(type) != allowedHazards.end();
}

void Player::addAllowed(HazardType type)
{
    allowedHazards.insert(type);
}

// Gems
bool Player::canTouch(GemType type) const
{
    return allowedGems.find(type) != allowedGems.end();
}

void Player::addAllowed(GemType type)
{
    allowedGems.insert(type);
}

void Player::addGem() { gemCount++; }
int Player::getGemCount() const { return gemCount; }
void Player::resetGemCount() { gemCount = 0; }

// Doors
bool Player::canTouch(DoorType type) const
{
    return allowedDoors.find(type) != allowedDoors.end();
}

void Player::addAllowed(DoorType type)
{
    allowedDoors.insert(type);
}

void Player::setSpawnPoint(float x, float y)
{
    spawnX = x;
    spawnY = y;
}

void Player::respawn()
{
    shape.setPosition(spawnX, spawnY);
    velocityX = 0.f;
    velocityY = 0.f;
    previousX = spawnX;
    animator.resetToIdle();
    animator.syncPosition(shape.getPosition(), shape.getSize());
}
