#include "Game.hpp"
#include "Hazard.hpp"
#include "Platform.hpp"
// for debugging
#include <iostream>

Game::Game()
    : window(sf::VideoMode(768, 576), "2D Game", sf::Style::Titlebar | sf::Style::Close),
      playerOne(120.f, 500.f, sf::Color::Red, "warmsprite.png"),
      playerTwo(520.f, 500.f, sf::Color::Blue, "coldsprite.png"),
      playerOneInput(sf::Keyboard::A, sf::Keyboard::D, sf::Keyboard::W),
      playerTwoInput(sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Up)
{
    window.setFramerateLimit(60); // 60 FPS

    ground.setSize(sf::Vector2f(768.f, 50.f));
    ground.setFillColor(sf::Color(100, 70, 40));
    ground.setPosition(0.f, 550.f);

    // platforms init
    platforms.emplace_back(100.f, 400.f, 200.f, 20.f, PlatformType::notMoving);
    platforms.emplace_back(400.f, 300.f, 200.f, 20.f, PlatformType::movingVertically);

    // hazards init
    hazards.emplace_back(200.f, 500.f, 100.f, 50.f, HazardType::playerOneRiver);
    hazards.emplace_back(400.f, 500.f, 100.f, 50.f, HazardType::playerTwoRiver);
    hazards.emplace_back(600.f, 500.f, 100.f, 50.f, HazardType::generalRiver);

    // Player1 Player2 added into vector
    players.push_back(&playerOne);
    players.push_back(&playerTwo);

    // Player Rivers
    playerOne.addAllowed(HazardType::playerOneRiver);
    playerTwo.addAllowed(HazardType::playerTwoRiver);
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
    }
}

void Game::update()
{
    float dt = clock.restart().asSeconds();
    if (dt > 0.05f)
        dt = 0.05f;

    for(auto &platform : platforms)
    {
        platform.update(dt);
    }

    updatePlayer(playerOne, playerOneInput, dt);
    updatePlayer(playerTwo, playerTwoInput, dt);

    for (auto* p : players)
    {
        p->applyGravity(dt);
        collision.check(*p, ground, platforms, window);
    }

    for (auto *p : players)
    {
        for (auto &h : hazards)
        {
            if (collision.checkHazardCollision(*p, h))
            {
                if (h.getType() == HazardType::generalRiver || !p->canTouch(h.getType()))
                {
                    p->respawn();
                }
            }
        }
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

    playerTwo.draw(window);
    playerOne.draw(window);

    window.display();
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
