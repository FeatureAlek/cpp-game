#pragma once
#include <SFML/Graphics.hpp>
#include "Config.hpp"
#include "TextureManager.hpp"
#include "GameState.hpp"

class BackgroundManager
{
public:
    BackgroundManager(const sf::RenderWindow& window);
    void draw(sf::RenderWindow& window, GameState state);

private:
    sf::RectangleShape background;
    sf::RectangleShape menuBackground;

    void setupBackground(const sf::RenderWindow& window);
    void setupMenuBackground(const sf::RenderWindow& window);
};