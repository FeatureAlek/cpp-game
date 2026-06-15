#include "Game.hpp"
#include <fstream>

Game::Game()
    : window(sf::VideoMode(Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT), "2D Game", sf::Style::Titlebar | sf::Style::Close),
      playerOne(120.f, 500.f, sf::Color::Red, "textures/warmsprite.png"),
      playerTwo(520.f, 500.f, sf::Color::Blue, "textures/coldsprite.png"),
      playerOneInput(sf::Keyboard::A, sf::Keyboard::D, sf::Keyboard::W),
      playerTwoInput(sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Up),
      bgManager(window)
{
    window.setFramerateLimit(Config::FPS_LIMIT); // 60 FPS

    // Player1 Player2 added into vector
    players.push_back(&playerOne);
    players.push_back(&playerTwo);

    // Player Rivers
    playerOne.addAllowed(HazardType::playerOneRiver);
    playerTwo.addAllowed(HazardType::playerTwoRiver);

    // Player Gems
    playerOne.addAllowed(GemType::redGem);
    playerTwo.addAllowed(GemType::blueGem);

    // Player Doors
    playerOne.addAllowed(DoorType::playerOneDoor);
    playerTwo.addAllowed(DoorType::playerTwoDoor);

    loadMap("map.txt");
}

// Game loop
void Game::run()
{
    while (window.isOpen())
    {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::KeyPressed)
        {
            switch (gameState)
            {
            case GameState::MainMenu:
                handleMainMenuInput(event.key.code);
                break;
            case GameState::LevelSelect:
                handleLevelSelectInput(event.key.code);
                break;
            case GameState::Playing:
                handlePlayingInput(event.key.code);
                break;
            case GameState::Paused:
                handlePausedInput(event.key.code);
                break;
            case GameState::Win:
                handleWinInput(event.key.code);
                break;
            case GameState::Lose:
                handleLoseInput(event.key.code);
                break;
            }
        }
    }
}

void Game::handleMainMenuInput(sf::Keyboard::Key key)
{
    MenuAction action = ui.handleMainMenu(key);
    if (action == MenuAction::Play)
    {
        gameState = GameState::LevelSelect;
        ui.resetIndex();
    }
    if (action == MenuAction::Exit)
        window.close();
}

void Game::handleLevelSelectInput(sf::Keyboard::Key key)
{
    MenuAction action = ui.handleLevelSelect(key, Config::LEVEL_COUNT);
    if (action == MenuAction::LevelChosen)
    {
        loadLevel(ui.getSelectedLevel());
        gameState = GameState::Playing;
        sounds.stopAllSounds();
        sounds.playGameMusic();
        ui.resetIndex();
    }
    if (action == MenuAction::Back)
    {
        gameState = GameState::MainMenu;
        ui.resetIndex();
    }
}

void Game::handlePlayingInput(sf::Keyboard::Key key)
{
    if (key == sf::Keyboard::Escape)
    {
        gameState = GameState::Paused;
        ui.resetIndex();
    }
}

void Game::handlePausedInput(sf::Keyboard::Key key)
{
    MenuAction action = ui.handlePauseMenu(key);
    if (action == MenuAction::Resume)
    {
        gameState = GameState::Playing;
        ui.resetIndex();
    }
    if (action == MenuAction::Restart)
    {
        sounds.stopAllSounds();
        restart();
        sounds.playGameMusic();
        ui.resetIndex();
    }
    if (action == MenuAction::BackToLevels)
    {
        sounds.stopAllSounds();
        gameState = GameState::LevelSelect;
        sounds.playMenuMusic();
        ui.resetIndex();
    }
    if (action == MenuAction::Exit)
        window.close();
}

void Game::handleWinInput(sf::Keyboard::Key key)
{
    MenuAction action = ui.handleWinScreen(key);
    if (action == MenuAction::Continue)
    {
        sounds.stopAllSounds();
        gameState = GameState::LevelSelect;
        sounds.playMenuMusic();
        ui.resetIndex();
    }
    if (action == MenuAction::Restart)
    {
        sounds.stopAllSounds();
        restart();
        sounds.playGameMusic();
        ui.resetIndex();
    }
    if (action == MenuAction::Exit)
        window.close();
}

void Game::handleLoseInput(sf::Keyboard::Key key)
{
    MenuAction action = ui.handleLoseScreen(key);
    if (action == MenuAction::Restart)
    {
        sounds.stopAllSounds();
        restart();
        sounds.playGameMusic();
        ui.resetIndex();
    }
    if (action == MenuAction::BackToLevels)
    {
        sounds.stopAllSounds();
        gameState = GameState::LevelSelect;
        sounds.playMenuMusic();
        ui.resetIndex();
    }
    if (action == MenuAction::Exit)
        window.close();
}

void Game::restart()
{
    gameState = GameState::Playing;
    loadLevel(currentLevel);
}

void Game::update()
{
    if (gameState != GameState::Playing)
        return;

    float dt = clock.restart().asSeconds();
    if (dt > Config::MAX_DT)
        dt = Config::MAX_DT;

    updatePlatforms(dt);
    updateButtons();
    updatePlayers(dt);

    if (updateHazards())
        return;

    updateGems();
    updateDoors(dt);

    for (auto *p : players)
        p->updateAnimation(dt);
}

void Game::updatePlatforms(float dt)
{
    for (auto &platform : platforms)
        platform.update(dt);
}

void Game::updatePlayers(float dt)
{
    updatePlayer(playerOne, playerOneInput, dt);
    updatePlayer(playerTwo, playerTwoInput, dt);

    for (auto *p : players)
    {
        p->applyGravity(dt);
        collision.check(*p, platforms, window);
    }
}

bool Game::updateHazards()
{
    for (auto *p : players)
    {
        if (p->getBounds().top > window.getSize().y)
        {
            gameState = GameState::Lose;
            sounds.stopMusic();
            sounds.playDeathMusic();
            return true;
        }

        for (auto &h : hazards)
        {
            if (collision.checkHazardCollision(*p, h))
            {
                if (h.getType() == HazardType::generalRiver || !p->canTouch(h.getType()))
                {
                    gameState = GameState::Lose;
                    sounds.stopMusic();
                    sounds.playDeathMusic();
                    return true;
                }
            }
        }
    }
    return false;
}

void Game::updateGems()
{
    for (auto *p : players)
    {
        for (auto &g : gems)
        {
            if (!g.isCollected() && collision.checkGemCollision(*p, g))
            {
                if (p->canTouch(g.getType()))
                {
                    g.collect();
                    p->addGem();
                    sounds.playGemCollect();
                }
            }
        }
    }
}

void Game::updateDoors(float dt)
{
    bool p1AtDoor = false;
    bool p2AtDoor = false;

    for (auto *p : players)
    {
        for (auto &d : doors)
        {
            if (collision.checkDoorCollision(*p, d))
            {
                if (p->canTouch(d.getType()) && allGemsCollected())
                {
                    d.open();
                    if (d.getType() == DoorType::playerOneDoor)
                        p1AtDoor = true;
                    if (d.getType() == DoorType::playerTwoDoor)
                        p2AtDoor = true;
                }
            }
        }
    }

    if (p1AtDoor && p2AtDoor)
    {
        doorTimer += dt;
        if (doorTimer >= Config::DOOR_TIMER)
        {
            gameState = GameState::Win;
            sounds.stopMusic();
            sounds.playWin();
        }
    }
    else
    {
        doorTimer = 0.f;
    }
}

void Game::updateButtons()
{
    for (auto& b : buttons)
        b.setPressed(false);

    for (auto* p : players)
        for (auto& b : buttons)
            if (collision.checkButtonCollision(*p, b))
                b.setPressed(true);

    bool anyPressed = false;
    for (auto& b : buttons)
        if (b.isPressed())
            anyPressed = true;

    for (auto& p : platforms)
        if (p.getType() == PlatformType::buttonControlled)
            p.setActive(anyPressed);
}

void Game::render()
{
    window.clear(sf::Color(50, 50, 50));

    bgManager.draw(window, gameState);

    if (gameState != GameState::MainMenu && gameState != GameState::LevelSelect)
    {
        for (auto &platform : platforms)
            platform.draw(window);
        for (auto &h : hazards)
            h.draw(window);
        for (auto &g : gems)
            if (!g.isCollected())
                g.draw(window);
        for (auto &d : doors)
            d.draw(window);
        for (auto& b : buttons)
            b.draw(window);

        playerTwo.draw(window);
        playerOne.draw(window);

        if (gameState == GameState::Playing)
            ui.renderGemCounter(window, playerOne.getGemCount(), playerTwo.getGemCount());
        else if (gameState == GameState::Paused)
            ui.renderPauseMenu(window);
        else if (gameState == GameState::Win)
            ui.renderWinScreen(window, playerOne.getGemCount(), playerTwo.getGemCount());
        else if (gameState == GameState::Lose)
            ui.renderLoseScreen(window);
    }
    else
    {
        if (gameState == GameState::MainMenu)
            ui.renderMainMenu(window);
        else if (gameState == GameState::LevelSelect)
            ui.renderLevelSelect(window, Config::LEVEL_COUNT);
    }

    window.display();
}

bool Game::allGemsCollected()
{
    for (auto &g : gems)
        if (!g.isCollected())
            return false;
    return true;
}

void Game::updatePlayer(Player &player, const InputHandler &inputHandler, float dt)
{
    if (inputHandler.isLeftPressed())
        player.moveLeft(dt);
    if (inputHandler.isRightPressed())
        player.moveRight(dt);
    if (inputHandler.isJumpPressed())
        player.jump();
}

void Game::loadLevel(int levelIndex)
{
    currentLevel = levelIndex;
    buttons.clear();
    playerOne.resetGemCount();
    playerTwo.resetGemCount();
    doorTimer = 0.f;
    loadMap("map" + std::to_string(levelIndex + 1) + ".txt");
}

void Game::loadMap(const std::string &name)
{
    platforms.clear();
    hazards.clear();
    doors.clear();
    gems.clear();
    buttons.clear();

    std::ifstream in(std::string(GAME_ASSET_DIR) + "/" + name);
    if (!in)
        return;

    std::vector<std::string> rows;
    std::string line;
    const float tile = Config::TILE_SIZE;

    while (std::getline(in, line))
        rows.push_back(line);

    if (rows.empty())
        return;

    const float yOffset = 0.f;

    for (std::size_t row = 0; row < rows.size(); ++row)
    {
        for (std::size_t col = 0; col < rows[row].size(); ++col)
        {
            float x = static_cast<float>(col) * tile;
            float y = yOffset + static_cast<float>(row) * tile;

            switch (rows[row][col])
            {
            case '3':
                platforms.emplace_back(x, y, tile, tile, PlatformType::notMoving);
                break;
            case '4':
                platforms.emplace_back(x, y, tile, tile, PlatformType::movingVertically);
                break;
            case '5':
                hazards.emplace_back(x, y, tile, tile, HazardType::playerOneRiver);
                break;
            case '6':
                hazards.emplace_back(x, y, tile, tile, HazardType::playerTwoRiver);
                break;
            case '7':
                hazards.emplace_back(x, y, tile, tile, HazardType::generalRiver);
                break;
            case '1':
                playerOne.setSpawnPoint(
                    x + (tile - playerOne.getBounds().width) * 0.5f,
                    y + tile - playerOne.getBounds().height);
                break;
            case '2':
                playerTwo.setSpawnPoint(
                    x + (tile - playerTwo.getBounds().width) * 0.5f,
                    y + tile - playerTwo.getBounds().height);
                break;
            case 'R':
                gems.emplace_back(x, y, tile, tile, GemType::redGem);
                break;
            case 'B':
                gems.emplace_back(x, y, tile, tile, GemType::blueGem);
                break;
            case 'D':
                doors.emplace_back(x, y, tile, tile, DoorType::playerOneDoor);
                break;
            case 'd':
                doors.emplace_back(x, y, tile, tile, DoorType::playerTwoDoor);
                break;
            case 'b':
                buttons.emplace_back(x, y, tile, tile);
                break;
            case 'm':
                platforms.emplace_back(x, y, tile, tile, PlatformType::buttonControlled);
                break;

            case '.':
            case '8':
                break;
            }
        }
    }

    playerOne.respawn();
    playerTwo.respawn();
}
