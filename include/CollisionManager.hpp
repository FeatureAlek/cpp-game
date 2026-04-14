#pragma once
#include <SFML/Graphics.hpp>
#include <algorithm>
#include "Player.hpp"

class CollisionManager
{
public:
    void check(Player& player, const sf::RectangleShape& ground, std::vector<sf::RectangleShape>& platforms, sf::RenderWindow& window);
private:
    
};
