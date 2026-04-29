#include "CollisionManager.hpp"

void CollisionManager::check(Player &player, const sf::RectangleShape &ground, std::vector<Platform>& platforms, sf::RenderWindow &window)
{
    sf::FloatRect playerBounds = player.getBounds();

    // window - ground
    if (player.isOnGround(ground))
        player.stopFalling(ground);

    // platforms
    for (auto& platform : platforms)
        resolveCollision(player, platform.getBounds());

    // window - walls
    if (playerBounds.left < 0)
        player.setPositionX(0);
    if (playerBounds.left + playerBounds.width > window.getSize().x)
        player.setPositionX(window.getSize().x - playerBounds.width);
}

// AABB minimum overlap method
void CollisionManager::resolveCollision(Player& player, const sf::FloatRect& platformBounds)
{
    sf::FloatRect playerBounds = player.getBounds();

    if (!playerBounds.intersects(platformBounds)) return;

    int playerRightX    = playerBounds.left + playerBounds.width;
    int playerBottomY   = playerBounds.top + playerBounds.height;
    int platformRightX  = platformBounds.left + platformBounds.width;
    int platformBottomY = platformBounds.top + platformBounds.height;

    int overlapLeft   = playerRightX - platformBounds.left;
    int overlapRight  = platformRightX - playerBounds.left;
    int overlapTop    = playerBottomY - platformBounds.top;
    int overlapBottom = platformBottomY - playerBounds.top;

    int minOverlap = std::min({overlapLeft, overlapRight, overlapTop, overlapBottom});

    if (minOverlap == overlapLeft)
    {
        player.setPositionX(platformBounds.left - playerBounds.width);
        player.setVelocityX(0.f);
    }
    else if (minOverlap == overlapRight)
    {
        player.setPositionX(platformRightX);
        player.setVelocityX(0.f);
    }
    else if (minOverlap == overlapTop)
    {   
        float playerBottomBefore = player.getBounds().top + player.getBounds().height - player.getVelocityY();

        if (player.getVelocityY() >= 0.f)
        {
            player.setPositionY(platformBounds.top - playerBounds.height);
            player.setVelocityY(0.f);
            player.setOnGround(true);
        }
    }
    else if (minOverlap == overlapBottom)
    {
        if (player.getVelocityY() < 0.f)
        {
            player.setPositionY(platformBottomY);
            player.setVelocityY(0.f);
        }
    }
}

bool CollisionManager::checkHazardCollision(Player& player, Hazard& hazard){
    
    return player.getBounds().intersects(hazard.getBounds());
}