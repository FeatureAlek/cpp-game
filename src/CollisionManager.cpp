#include "CollisionManager.hpp"

void CollisionManager::check(Player &player, const sf::RectangleShape &ground, std::vector<sf::RectangleShape> &platforms, sf::RenderWindow &window)
{

    sf::FloatRect playerBounds = player.getBounds();

    // ground
    if (player.isOnGround(ground))
    {
        player.stopFalling(ground);
    }


        // platforms
    for (auto& platform : platforms)
    {
        sf::FloatRect platformBounds = platform.getGlobalBounds();

        int playerRightX = playerBounds.left + playerBounds.width;
        int playerBottomY = playerBounds.top + playerBounds.height;
        int platformRightX = platformBounds.left + platformBounds.width;
        int platformBottomY = platformBounds.top + platformBounds.height;

        if (playerBounds.intersects(platformBounds))
        {
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
                player.setPositionY(platformBounds.top - playerBounds.height);
                player.setVelocityY(0.f);
                player.setOnGround(true);
            }
            else if (minOverlap == overlapBottom)
            {
                player.setPositionY(platformBottomY);
                player.setVelocityY(0.f);
            }
        }
    }

    // walls
    float winWidth = window.getSize().x;

    if (playerBounds.left < 0)
    {
        player.setPositionX(0);
    }

    if (playerBounds.left + playerBounds.width > winWidth)
    {
        player.setPositionX(winWidth - playerBounds.width);
    }
}