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
    drawText(window, title, 300.f, 100.f, 48, sf::Color::Yellow);

    // menu items
    for (std::size_t i = 0; i < items.size(); ++i)
    {
        bool isSelected = (static_cast<int>(i) == selectedIndex);
        drawText(window,
                 isSelected ? "> " + items[i] : items[i],
                 320.f, 220.f + i * 60.f, 32,
                 isSelected ? sf::Color::Yellow : sf::Color::White);
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
    drawText(window,
             "Player 1 gems: " + std::to_string(p1Gems) + "\n" +
                 "Player 2 gems: " + std::to_string(p2Gems),
             280.f, 460.f, 24, sf::Color::White);
}

void UI::renderGemCounter(sf::RenderWindow &window, int p1Gems, int p2Gems)
{
    drawText(window,
             "P1: " + std::to_string(p1Gems) +
                 "  P2: " + std::to_string(p2Gems),
             10.f, 10.f, 20, sf::Color::White);
}

void UI::renderLoseScreen(sf::RenderWindow &window)
{
    renderMenu(window, "You Lose!", {"Restart", "Back to Levels", "Exit"});
}

void UI::renderLevelSelect(sf::RenderWindow &window, int levelCount)
{
    // Overlay
    sf::RectangleShape overlay(sf::Vector2f(768.f, 576.f));
    overlay.setFillColor(sf::Color(0, 0, 0, 180));
    window.draw(overlay);

    // Name
    drawText(window, "Select Level", 250.f, 60.f, 48, sf::Color::Yellow);

    // Levels
    const float colX[2] = {180.f, 420.f};
    const float startY = 160.f, stepY = 70.f;
    const int rowCount = (levelCount + 1) / 2;

    for (int i = 0; i < levelCount; ++i)
    {
        float x = colX[i / rowCount];
        float y = startY + (i % rowCount) * stepY;

        bool isSelected = (i == selectedIndex);
        std::string prefix = isSelected ? "> " : "";
        sf::Color color = isSelected ? sf::Color::Yellow : sf::Color::White;

        drawText(window, prefix + "Level " + std::to_string(i + 1), x, y, 32, color);
    }

    // Back button
    bool isBackSelected = (selectedIndex == levelCount);
    float backY = startY + (levelCount / 2) * stepY + 20.f;

    drawText(window, isBackSelected ? "> Back" : "Back", 300.f, backY, 32,
             isBackSelected ? sf::Color::Yellow : sf::Color::White);
}

void UI::renderInstructions(sf::RenderWindow &window)
{
    // Mini window
    sf::RectangleShape panel(sf::Vector2f(500.f, 400.f));
    panel.setFillColor(sf::Color(20, 20, 20, 230));
    panel.setOutlineColor(sf::Color::White);
    panel.setOutlineThickness(2.f);
    panel.setPosition(134.f, 100.f);
    window.draw(panel);

    // Title
    drawText(window, "How to Play", 290.f, 120.f, 36, sf::Color::Yellow);

    // Instruction text
    std::string instructions =
        "Player 1 (Red):\n"
        "  - Move: A / D\n"
        "  - Jump: W\n\n"
        "Player 2 (Blue):\n"
        "  - Move: Left / Right\n"
        "  - Jump: Up\n\n"
        "Collect all gems and reach\n"
        "the door to win!\n\n"
        "Step on buttons to activate\n"
        "platforms.";

    drawText(window, instructions, 160.f, 180.f, 18, sf::Color::White);

    // OK Button
    bool isOkSelected = (selectedIndex == 0);

    drawText(window,
             isOkSelected ? "> OK" : "OK",
             370.f, 450.f, 24,
             isOkSelected ? sf::Color::Yellow : sf::Color::White);
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

void UI::drawText(sf::RenderWindow &window, const std::string &str, float x, float y, unsigned int size, sf::Color color)
{
    sf::Text text;
    text.setFont(font);
    text.setString(str);
    text.setCharacterSize(size);
    text.setFillColor(color);
    text.setPosition(x, y);
    window.draw(text);
}

void UI::resetIndex() { selectedIndex = 0; }