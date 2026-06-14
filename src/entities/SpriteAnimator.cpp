#include "SpriteAnimator.hpp"
#include "Config.hpp"
#include <cmath>

bool SpriteAnimator::load(const std::string &spriteFile)
{
    if (spriteFile.empty())
        return false;
    createSpriteSheet(spriteFile);
    return hasSprite;
}

void SpriteAnimator::createSpriteSheet(const std::string &spriteFile)
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
}

void SpriteAnimator::update(float dt, float currentX, float previousX)
{
    if (!hasSprite)
        return;

    const bool isWalking = std::fabs(currentX - previousX) > 0.01f;

    if (isWalking)
    {
        animationTimer += dt;
        while (animationTimer >= Config::SPRITE_ANIMATION_STEP)
        {
            animationTimer -= Config::SPRITE_ANIMATION_STEP;
            animationIndex = (animationIndex + 1) % std::size(Config::SPRITE_ANIMATION_FRAMES);
        }
        updateTextureRect();
    }
    else
    {
        animationTimer = 0.f;
        animationIndex = 0;
        updateTextureRect(Config::SPRITE_IDLE_FRAME);
    }
}

void SpriteAnimator::syncPosition(sf::Vector2f position, sf::Vector2f hitboxSize)
{
    if (!hasSprite)
        return;
    syncVisualPosition(position, hitboxSize);
}

void SpriteAnimator::syncVisualPosition(sf::Vector2f position, sf::Vector2f hitboxSize)
{
    const float visualWidth = Config::SPRITE_FRAME_SIZE * std::fabs(sprite.getScale().x);
    const float visualHeight = Config::SPRITE_FRAME_SIZE * std::fabs(sprite.getScale().y);
    const float offsetX = (hitboxSize.x - visualWidth) * 0.5f;
    const float offsetY = hitboxSize.y - visualHeight;
    sprite.setPosition(position.x + offsetX, position.y + offsetY);
}

void SpriteAnimator::setFacingRight(bool right)
{
    facingRight = right;
}

void SpriteAnimator::resetToIdle()
{
    animationTimer = 0.f;
    animationIndex = 0;
    updateTextureRect(Config::SPRITE_IDLE_FRAME);
}

void SpriteAnimator::draw(sf::RenderWindow &window)
{
    if (hasSprite)
        window.draw(sprite);
}

void SpriteAnimator::updateTextureRect(int frame)
{
    if (!hasSprite)
        return;
    const int selectedFrame = (frame >= 0) ? frame : Config::SPRITE_ANIMATION_FRAMES[animationIndex];
    const int frameX = (selectedFrame % 2) * Config::SPRITE_FRAME_SIZE;
    const int frameY = (selectedFrame / 2) * Config::SPRITE_FRAME_SIZE;

    if (facingRight)
        sprite.setTextureRect(sf::IntRect(frameX + Config::SPRITE_FRAME_SIZE, frameY,
                                          -Config::SPRITE_FRAME_SIZE, Config::SPRITE_FRAME_SIZE));
    else
        sprite.setTextureRect(sf::IntRect(frameX, frameY,
                                          Config::SPRITE_FRAME_SIZE, Config::SPRITE_FRAME_SIZE));
}