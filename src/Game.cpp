#include "Game.hpp"
#include "Platform.hpp"
#include <fstream>
// for debugging
#include <iostream>

namespace
{
    sf::Texture *getTileTexture()
    {
        static sf::Texture texture;
        static bool attemptedLoad = false;

        if (!attemptedLoad)
        {
            texture.loadFromFile(std::string(GAME_ASSET_DIR) + "/tile.png");
            texture.setRepeated(true);
            attemptedLoad = true;
        }

        if (texture.getSize().x == 0 || texture.getSize().y == 0)
            return nullptr;

        return &texture;
    }
}

Game::Game()
    : window(sf::VideoMode(768, 576), "2D Game", sf::Style::Titlebar | sf::Style::Close),
      playerOne(120.f, 500.f, sf::Color::Red, "warmsprite.png"),
      playerTwo(520.f, 500.f, sf::Color::Blue, "coldsprite.png"),
      playerOneInput(sf::Keyboard::A, sf::Keyboard::D, sf::Keyboard::W),
      playerTwoInput(sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Up)
{
    window.setFramerateLimit(60); // 60 FPS

    ground.setSize(sf::Vector2f(0.f, 0.f));
    if (sf::Texture *texture = getTileTexture())
    {
        ground.setTexture(texture);
        ground.setTextureRect(sf::IntRect(0, 0, 768, 50));
        ground.setFillColor(sf::Color::White);
    }

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

// Window close button
void Game::processEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::KeyPressed)
        {
            if (gameState == GameState::MainMenu)
            {
                MenuAction action = ui.handleMainMenu(event.key.code);
                if (action == MenuAction::Play)
                {
                    gameState = GameState::Playing;
                    ui.resetIndex();
                }
                if (action == MenuAction::Exit)
                    window.close();
            }
            else if (gameState == GameState::Paused)
            {
                MenuAction action = ui.handlePauseMenu(event.key.code);
                if (action == MenuAction::Resume)
                {
                    gameState = GameState::Playing;
                    ui.resetIndex();
                }
                if (action == MenuAction::Restart)
                {
                    restart();
                    ui.resetIndex();
                }
                if (action == MenuAction::Exit)
                    window.close();
            }
            else if (gameState == GameState::Win)
            {
                MenuAction action = ui.handleWinScreen(event.key.code);
                if (action == MenuAction::Restart)
                {
                    restart();
                    ui.resetIndex();
                }
                if (action == MenuAction::Exit)
                    window.close();
            }
            else if (gameState == GameState::Playing)
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    gameState = GameState::Paused;
                    ui.resetIndex();
                }
            }
            else if (gameState == GameState::Lose)
            {
                MenuAction action = ui.handleLoseScreen(event.key.code);
                if (action == MenuAction::Restart)
                {
                    restart();
                    ui.resetIndex();
                }
                if (action == MenuAction::Exit)
                    window.close();
            }
        }
    }
}

void Game::restart()
{   
    playerOne.resetGemCount();
    playerTwo.resetGemCount();
    gameState = GameState::Playing;
    doorTimer = 0.f;
    loadMap("map.txt");
}

void Game::update()
{
    if (gameState != GameState::Playing)
        return;

    float dt = clock.restart().asSeconds();
    if (dt > 0.05f)
        dt = 0.05f;

    for (auto &platform : platforms)
    {
        platform.update(dt);
    }

    updatePlayer(playerOne, playerOneInput, dt);
    updatePlayer(playerTwo, playerTwoInput, dt);

    for (auto *p : players)
    {
        p->applyGravity(dt);
        collision.check(*p, platforms, window);

        if (p->getBounds().top > window.getSize().y)
        {
            gameState = GameState::Lose;
            return;
        }
    }

    for (auto *p : players)
    {
        for (auto &h : hazards)
        {
            if (collision.checkHazardCollision(*p, h))
            {
                if (h.getType() == HazardType::generalRiver || !p->canTouch(h.getType()))
                {   
                    gameState = GameState::Lose;
                    return;
                }
            }
        }
    }

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
                }
            }
        }
    }

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
        if (doorTimer >= 2.f)
            gameState = GameState::Win;
    }
    else
    {
        doorTimer = 0.f;
    }

    for (auto *p : players)
        p->updateAnimation(dt);
}

void Game::render()
{
    window.clear(sf::Color(50, 50, 50));

    window.draw(ground);

    for (auto &platform : platforms)
    {
        platform.draw(window);
    }

    for (auto &h : hazards)
    {
        h.draw(window);
    }

    for (auto &g : gems)
    {
        if (!g.isCollected())
            g.draw(window);
    }

    for (auto &d : doors)
    {
        d.draw(window);
    }

    playerTwo.draw(window);
    playerOne.draw(window);

    if (gameState == GameState::Playing)
        ui.renderGemCounter(window, playerOne.getGemCount(), playerTwo.getGemCount());
    else if (gameState == GameState::Win)
        ui.renderWinScreen(window, playerOne.getGemCount(), playerTwo.getGemCount());
    else if (gameState == GameState::MainMenu)
        ui.renderMainMenu(window);
    else if (gameState == GameState::Paused)
        ui.renderPauseMenu(window);
    else if (gameState == GameState::Lose)
        ui.renderLoseScreen(window);

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

void Game::loadMap(const std::string &name)
{
    platforms.clear();
    hazards.clear();
    doors.clear();
    gems.clear();

    std::ifstream in(std::string(GAME_ASSET_DIR) + "/" + name);
    if (!in)
        return;

    std::vector<std::string> rows;
    std::string line;
    const float tile = 32.f;

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

            case '.':
            case '8':
                break;
            }
        }
    }

    playerOne.respawn();
    playerTwo.respawn();
}
