#pragma once
#include <SFML/Graphics.hpp>
#include "Player.hpp"

class CollisionManager
{
public:
    void check(Player& player, const sf::RectangleShape& ground, sf::RenderWindow& window);
private:

};
