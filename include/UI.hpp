#pragma once
#include <SFML/Graphics.hpp>

enum class MenuAction
{
    None,
    Play,
    Resume,
    Restart,
    Exit
};

class UI
{
public:
    UI();
    void renderMainMenu(sf::RenderWindow &window);
    void renderPauseMenu(sf::RenderWindow &window);
    void renderWinScreen(sf::RenderWindow &window, int p1Gems, int p2Gems);
    void renderGemCounter(sf::RenderWindow &window, int p1Gems, int p2Gems);

    MenuAction handleMainMenu(sf::Keyboard::Key key);
    MenuAction handlePauseMenu(sf::Keyboard::Key key);
    MenuAction handleWinScreen(sf::Keyboard::Key key);

    void resetIndex();

private:
    sf::Font font;

    int selectedIndex = 0;

    void renderMenu(sf::RenderWindow &window, const std::string &title,
                    const std::vector<std::string> &items);
};