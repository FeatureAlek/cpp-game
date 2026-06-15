#pragma once
#include <SFML/Graphics.hpp>

enum class MenuAction
{
    None,
    Play,
    Resume,
    Restart,
    Exit,
    LevelSelect,
    LevelChosen,
    BackToLevels,
    Continue,
    Back,
    Instructions
};

class UI
{
public:
    UI();
    void renderMainMenu(sf::RenderWindow &window);
    void renderPauseMenu(sf::RenderWindow &window);
    void renderWinScreen(sf::RenderWindow &window, int p1Gems, int p2Gems);
    void renderGemCounter(sf::RenderWindow &window, int p1Gems, int p2Gems);
    void renderLoseScreen(sf::RenderWindow &window);
    void renderLevelSelect(sf::RenderWindow &window, int levelCount);
    void renderInstructions(sf::RenderWindow& window);

    MenuAction handleMainMenu(sf::Keyboard::Key key);
    MenuAction handlePauseMenu(sf::Keyboard::Key key);
    MenuAction handleWinScreen(sf::Keyboard::Key key);
    MenuAction handleLoseScreen(sf::Keyboard::Key key);
    MenuAction handleLevelSelect(sf::Keyboard::Key key, int levelCount);
    MenuAction handleInstructions(sf::Keyboard::Key key);

    void resetIndex();
    int getSelectedLevel() const { return selectedIndex; }


private:
    sf::Font font;

    int selectedIndex = 0; // choice

    void renderMenu(sf::RenderWindow &window, const std::string &title,
                    const std::vector<std::string> &items);

    // helper function
    void drawText(sf::RenderWindow &window, const std::string &str, float x, float y, unsigned int size, sf::Color color);
};