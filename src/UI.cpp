#include "UI.hpp"

UI::UI()
{
    font.loadFromFile(std::string(GAME_ASSET_DIR) + "/DEBUGfont.ttf");
}

void UI::renderWinScreen(sf::RenderWindow& window, int p1Gems, int p2Gems)
{
    sf::RectangleShape overlay(sf::Vector2f(768.f, 576.f));
    overlay.setFillColor(sf::Color(0, 0, 0, 150));
    window.draw(overlay);

    sf::Text title;
    title.setFont(font);
    title.setString("You Win!");
    title.setCharacterSize(48);
    title.setFillColor(sf::Color::Yellow);
    title.setPosition(300.f, 150.f);
    window.draw(title);

    sf::Text stats;
    stats.setFont(font);
    stats.setString("Player 1 gems: " + std::to_string(p1Gems) + "\n" +
                    "Player 2 gems: " + std::to_string(p2Gems));
    stats.setCharacterSize(28);
    stats.setFillColor(sf::Color::White);
    stats.setPosition(250.f, 250.f);
    window.draw(stats);

    sf::Text restart;
    restart.setFont(font);
    restart.setString("Press R to restart");
    restart.setCharacterSize(24);
    restart.setFillColor(sf::Color::White);
    restart.setPosition(270.f, 400.f);
    window.draw(restart);
}

void UI::renderGemCounter(sf::RenderWindow& window, int p1Gems, int p2Gems)
{
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::White);
    text.setString("P1 gems: " + std::to_string(p1Gems) +
                   "  P2 gems: " + std::to_string(p2Gems));
    text.setPosition(10.f, 10.f);
    window.draw(text);
}