#include "UI.hpp"

UI::UI()
{
    font.loadFromFile(std::string(GAME_ASSET_DIR) + "/DEBUGfont.ttf");
}

void UI::renderMenu(sf::RenderWindow &window, const std::string &title,
                    const std::vector<std::string> &items)
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

void UI::renderMainMenu(sf::RenderWindow &window)
{
    renderMenu(window, "2D Game", {"Play", "Instructions", "Exit"});
}

void UI::renderPauseMenu(sf::RenderWindow &window)
{
    renderMenu(window, "Paused", {"Resume", "Restart", "Back to Levels", "Exit Game"});
}

void UI::renderWinScreen(sf::RenderWindow &window, int p1Gems, int p2Gems)
{
    renderMenu(window, "You Win!", {"Continue", "Restart", "Exit"});

    sf::Text stats;
    stats.setFont(font);
    stats.setString("Player 1 gems: " + std::to_string(p1Gems) + "\n" +
                    "Player 2 gems: " + std::to_string(p2Gems));
    stats.setCharacterSize(24);
    stats.setFillColor(sf::Color::White);
    stats.setPosition(280.f, 460.f);
    window.draw(stats);
}

void UI::renderGemCounter(sf::RenderWindow &window, int p1Gems, int p2Gems)
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

void UI::renderLoseScreen(sf::RenderWindow &window)
{
    renderMenu(window, "You Lose!", {"Restart", "Back to Levels", "Exit"});
}

void UI::renderLevelSelect(sf::RenderWindow &window, int levelCount)
{
    std::vector<std::string> items;
    for (int i = 0; i < levelCount; ++i)
        items.push_back("Level " + std::to_string(i + 1));
    items.push_back("Back");

    renderMenu(window, "Select Level", items);
}

void UI::renderInstructions(sf::RenderWindow &window)
{
    // mini window
    sf::RectangleShape panel(sf::Vector2f(500.f, 400.f));
    panel.setFillColor(sf::Color(20, 20, 20, 230));
    panel.setOutlineColor(sf::Color::White);
    panel.setOutlineThickness(2.f);
    panel.setPosition(134.f, 100.f);
    window.draw(panel);

    // title
    sf::Text title;
    title.setFont(font);
    title.setString("How to Play");
    title.setCharacterSize(36);
    title.setFillColor(sf::Color::Yellow);
    title.setPosition(290.f, 120.f);
    window.draw(title);

    // Instructions
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(18);
    text.setFillColor(sf::Color::White);
    text.setString(
        "Player 1 (Red):\n"
        "  - Move: A / D\n"
        "  - Jump: W\n\n"
        "Player 2 (Blue):\n"
        "  - Move: Left / Right\n"
        "  - Jump: Up\n\n"
        "Collect all gems and reach\n"
        "the door to win!\n\n"
        "Step on buttons to activate\n"
        "platforms.");
    text.setPosition(160.f, 180.f);
    window.draw(text);

    // OK button
    sf::Text ok;
    ok.setFont(font);
    ok.setCharacterSize(24);
    ok.setPosition(370.f, 450.f);

    if (selectedIndex == 0)
    {
        ok.setFillColor(sf::Color::Yellow);
        ok.setString("> OK");
    }
    else
    {
        ok.setFillColor(sf::Color::White);
        ok.setString("OK");
    }
    window.draw(ok);
}

MenuAction UI::handleInstructions(sf::Keyboard::Key key)
{
    if (key == sf::Keyboard::Return)
        return MenuAction::Back;
    return MenuAction::None;
}

MenuAction UI::handleMainMenu(sf::Keyboard::Key key)
{
    if (key == sf::Keyboard::Up)
        selectedIndex = (selectedIndex - 1 + 3) % 3;
    if (key == sf::Keyboard::Down)
        selectedIndex = (selectedIndex + 1) % 3;
    if (key == sf::Keyboard::Return)
    {
        if (selectedIndex == 0)
            return MenuAction::Play;
        if (selectedIndex == 1)
            return MenuAction::Instructions;
        if (selectedIndex == 2)
            return MenuAction::Exit;
    }
    return MenuAction::None;
}

MenuAction UI::handlePauseMenu(sf::Keyboard::Key key)
{
    if (key == sf::Keyboard::Up)
        selectedIndex = (selectedIndex - 1 + 4) % 4;
    if (key == sf::Keyboard::Down)
        selectedIndex = (selectedIndex + 1) % 4;
    if (key == sf::Keyboard::Return)
    {
        if (selectedIndex == 0)
            return MenuAction::Resume;
        if (selectedIndex == 1)
            return MenuAction::Restart;
        if (selectedIndex == 2)
            return MenuAction::BackToLevels;
        if (selectedIndex == 3)
            return MenuAction::Exit;
    }
    return MenuAction::None;
}

MenuAction UI::handleWinScreen(sf::Keyboard::Key key)
{
    if (key == sf::Keyboard::Up)
        selectedIndex = (selectedIndex - 1 + 3) % 3;
    if (key == sf::Keyboard::Down)
        selectedIndex = (selectedIndex + 1) % 3;
    if (key == sf::Keyboard::Return)
    {
        if (selectedIndex == 0)
            return MenuAction::Continue;
        if (selectedIndex == 1)
            return MenuAction::Restart;
        if (selectedIndex == 2)
            return MenuAction::Exit;
    }
    return MenuAction::None;
}

MenuAction UI::handleLoseScreen(sf::Keyboard::Key key)
{
    if (key == sf::Keyboard::Up)
        selectedIndex = (selectedIndex - 1 + 3) % 3;
    if (key == sf::Keyboard::Down)
        selectedIndex = (selectedIndex + 1) % 3;
    if (key == sf::Keyboard::Return)
    {
        if (selectedIndex == 0)
            return MenuAction::Restart;
        if (selectedIndex == 1)
            return MenuAction::BackToLevels;
        if (selectedIndex == 2)
            return MenuAction::Exit;
    }
    return MenuAction::None;
}

MenuAction UI::handleLevelSelect(sf::Keyboard::Key key, int levelCount)
{
    int total = levelCount + 1;

    if (key == sf::Keyboard::Up)
        selectedIndex = (selectedIndex - 1 + total) % total;
    if (key == sf::Keyboard::Down)
        selectedIndex = (selectedIndex + 1) % total;
    if (key == sf::Keyboard::Return)
    {
        if (selectedIndex == levelCount)
            return MenuAction::Back;
        return MenuAction::LevelChosen;
    }
    return MenuAction::None;
}

void UI::resetIndex() { selectedIndex = 0; }