#pragma once
#include <SFML/Graphics.hpp>

class UI
{
public:
    UI();
    void renderWinScreen(sf::RenderWindow& window, int p1Gems, int p2Gems);
    void renderGemCounter(sf::RenderWindow& window, int p1Gems, int p2Gems);

private:
    sf::Font font;
};