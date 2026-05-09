#pragma once
#include <SFML/Graphics.hpp>
#include <algorithm>
#include "Player.hpp"
#include "Hazard.hpp"
#include "Platform.hpp"
#include "Gem.hpp"

class CollisionManager
{
public:
    void check(Player& player, std::vector<Platform>& platforms, sf::RenderWindow& window);
    bool checkHazardCollision(Player& player, Hazard& hazard);
    bool checkGemCollision(Player& player, Gem& gem);

private:
    void resolveCollision(Player& player, const sf::FloatRect& platformBounds);
};