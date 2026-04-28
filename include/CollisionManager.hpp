#pragma once
#include <SFML/Graphics.hpp>
#include <algorithm>
#include "Player.hpp"
#include "Hazard.hpp"

class CollisionManager
{
public:
    void check(Player& player, const sf::RectangleShape& ground, std::vector<sf::RectangleShape>& platforms, sf::RenderWindow& window);
    bool checkHazardCollision(Player& player, Hazard& hazard);
private:
    void resolveCollision(Player& player, const sf::RectangleShape& platform);
};
