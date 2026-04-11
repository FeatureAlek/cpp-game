#include "CollisionManager.hpp"

void CollisionManager::check(Player& player, const sf::RectangleShape& ground, sf::RenderWindow& window)
{
    // ground
    if(player.isOnGround(ground))
        player.stopFalling(ground);

    sf::FloatRect bounds = player.getBounds();
    float winWidth = window.getSize().x;

    if(bounds.left < 0)
        player.setPositionX(0);
        
    if(bounds.left + bounds.width > winWidth)
        player.setPositionX(winWidth - bounds.width);

}