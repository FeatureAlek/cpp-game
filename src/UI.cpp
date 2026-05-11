#include "UI.hpp"

UI::UI()
{
    font.loadFromFile(std::string(GAME_ASSET_DIR) + "/DEBUGfont.ttf");
}

void UI::renderMenu(sf::RenderWindow& window, const std::string& title,
                    const std::vector<std::string>& items)
{
    // overlay
    sf::RectangleShape overlay(sf::Vector2f(768.f, 576.f));
    overlay.setFillColor(sf::Color(0, 0, 0, 180));
    window.draw(overlay);

    // title
    sf::Text titleText;
    titleText.setFont(font);
    titleText.setString(title);
    titleText.setCharacterSize(48);
    titleText.setFillColor(sf::Color::Yellow);
    titleText.setPosition(300.f, 100.f);
    window.draw(titleText);

    // menu items
    for (std::size_t i = 0; i < items.size(); ++i)
    {
        sf::Text item;
        item.setFont(font);
        item.setString(items[i]);
        item.setCharacterSize(32);
        item.setPosition(320.f, 220.f + i * 60.f);

        if (static_cast<int>(i) == selectedIndex)
        {
            item.setFillColor(sf::Color::Yellow); // pasirinktas
            item.setString("> " + items[i]);
        }
        else
        {
            item.setFillColor(sf::Color::White);
        }
        window.draw(item);
    }
}

void UI::renderMainMenu(sf::RenderWindow& window)
{
    renderMenu(window, "2D Game", {"Play", "Exit"});
}

void UI::renderPauseMenu(sf::RenderWindow& window)
{
    renderMenu(window, "Paused", {"Resume", "Restart", "Exit"});
}

void UI::renderWinScreen(sf::RenderWindow& window, int p1Gems, int p2Gems)
{
    renderMenu(window, "You Win!", {"Restart", "Exit"});

    sf::Text stats;
    stats.setFont(font);
    stats.setString("Player 1 gems: " + std::to_string(p1Gems) + "\n" +
                    "Player 2 gems: " + std::to_string(p2Gems));
    stats.setCharacterSize(24);
    stats.setFillColor(sf::Color::White);
    stats.setPosition(280.f, 460.f);
    window.draw(stats);
}

void UI::renderGemCounter(sf::RenderWindow& window, int p1Gems, int p2Gems)
{
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::White);
    text.setString("P1: " + std::to_string(p1Gems) +
                   "  P2: " + std::to_string(p2Gems));
    text.setPosition(10.f, 10.f);
    window.draw(text);
}

MenuAction UI::handleMainMenu(sf::Keyboard::Key key)
{
    if (key == sf::Keyboard::Up)
        selectedIndex = (selectedIndex - 1 + 2) % 2;
    if (key == sf::Keyboard::Down)
        selectedIndex = (selectedIndex + 1) % 2;
    if (key == sf::Keyboard::Return)
    {
        if (selectedIndex == 0) return MenuAction::Play;
        if (selectedIndex == 1) return MenuAction::Exit;
    }
    return MenuAction::None;
}

MenuAction UI::handlePauseMenu(sf::Keyboard::Key key)
{
    if (key == sf::Keyboard::Up)
        selectedIndex = (selectedIndex - 1 + 3) % 3;
    if (key == sf::Keyboard::Down)
        selectedIndex = (selectedIndex + 1) % 3;
    if (key == sf::Keyboard::Return)
    {
        if (selectedIndex == 0) return MenuAction::Resume;
        if (selectedIndex == 1) return MenuAction::Restart;
        if (selectedIndex == 2) return MenuAction::Exit;
    }
    return MenuAction::None;
}

MenuAction UI::handleWinScreen(sf::Keyboard::Key key)
{
    if (key == sf::Keyboard::Up)
        selectedIndex = (selectedIndex - 1 + 2) % 2;
    if (key == sf::Keyboard::Down)
        selectedIndex = (selectedIndex + 1) % 2;
    if (key == sf::Keyboard::Return)
    {
        if (selectedIndex == 0) return MenuAction::Restart;
        if (selectedIndex == 1) return MenuAction::Exit;
    }
    return MenuAction::None;
}

void UI::resetIndex() { selectedIndex = 0; }