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
        createSpriteSheet(spriteFile);
}

void Player::moveLeft(float dt)
{
    facingRight = false;
    shape.move(-speed * dt, 0.f);
    syncVisualPosition();
}

void Player::moveRight(float dt)
{
    facingRight = true;
    shape.move(speed * dt, 0.f);
    syncVisualPosition();
}

void Player::draw(sf::RenderWindow &window)
{
    if (hasSprite)
        window.draw(sprite);
    else
        window.draw(shape);
}

void Player::updateAnimation(float dt)
{
    if (!hasSprite)
        return;

    const float currentX = shape.getPosition().x;
    const bool isWalking = std::fabs(currentX - previousX) > 0.01f;

    if (isWalking)
    {
        animationTimer += dt;

        while (animationTimer >= Config::SPRITE_ANIMATION_STEP)
        {
            animationTimer -= Config::SPRITE_ANIMATION_STEP;
            animationIndex = (animationIndex + 1) % std::size(Config::SPRITE_ANIMATION_FRAMES);
        }
    }
    else
    {
        animationTimer = 0.f;
        animationIndex = 0;
        updateTextureRect(Config::SPRITE_IDLE_FRAME);
    }

    previousX = currentX;
    if (isWalking)
        updateTextureRect();
    syncVisualPosition();
}

void Player::applyGravity(float dt)
{
    velocityY += gravity * dt;
    shape.move(0.f, velocityY * dt);
    syncVisualPosition();
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
    syncVisualPosition();
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
    syncVisualPosition();
}

void Player::setPositionY(float y)
{
    shape.setPosition(shape.getPosition().x, y);
    syncVisualPosition();
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
    animationTimer = 0.f;
    animationIndex = 0;
    previousX = spawnX;
    updateTextureRect(Config::SPRITE_IDLE_FRAME);
    syncVisualPosition();
}

void Player::syncVisualPosition()
{
    if (!hasSprite)
        return;

    const float visualWidth = Config::SPRITE_FRAME_SIZE * std::fabs(sprite.getScale().x);
    const float visualHeight = Config::SPRITE_FRAME_SIZE * std::fabs(sprite.getScale().y);
    const float offsetX = (shape.getSize().x - visualWidth) * 0.5f;
    const float offsetY = shape.getSize().y - visualHeight;

    sprite.setPosition(shape.getPosition().x + offsetX, shape.getPosition().y + offsetY);
}

void Player::updateTextureRect(int frame)
{
    if (!hasSprite)
        return;

    const int selectedFrame = (frame >= 0) ? frame : Config::SPRITE_ANIMATION_FRAMES[animationIndex];
    const int frameX = (selectedFrame % 2) * Config::SPRITE_FRAME_SIZE;
    const int frameY = (selectedFrame / 2) * Config::SPRITE_FRAME_SIZE;

    if (facingRight)
        sprite.setTextureRect(sf::IntRect(frameX + Config::SPRITE_FRAME_SIZE, frameY, -Config::SPRITE_FRAME_SIZE, Config::SPRITE_FRAME_SIZE));
    else
        sprite.setTextureRect(sf::IntRect(frameX, frameY, Config::SPRITE_FRAME_SIZE, Config::SPRITE_FRAME_SIZE));
}

void Player::createSpriteSheet(const std::string &spriteFile)
{
    const std::string spritePath = std::string(GAME_ASSET_DIR) + "/" + spriteFile;

    if (!spriteSheet.loadFromFile(spritePath))
    {
        hasSprite = false;
        return;
    }

    hasSprite = true;
    sprite.setTexture(spriteSheet);
    sprite.setScale(
        (Config::PLAYER_HITBOX * Config::SPRITE_VISUAL_SCALE) / static_cast<float>(Config::SPRITE_FRAME_SIZE),
        (Config::PLAYER_HITBOX * Config::SPRITE_VISUAL_SCALE) / static_cast<float>(Config::SPRITE_FRAME_SIZE));

    updateTextureRect(Config::SPRITE_IDLE_FRAME);
    syncVisualPosition();
}
