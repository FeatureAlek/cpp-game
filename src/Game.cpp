#include "Game.hpp"

Game::Game()
: window(sf::VideoMode(768,576), "2D Game", sf::Style::Titlebar | sf::Style::Close),
  playerOne(250.f, 250.f, sf::Color::Green),
  playerTwo(450.f, 250.f, sf::Color::Blue),
  playerOneInput(sf::Keyboard::A, sf::Keyboard::D, sf::Keyboard::W),
  playerTwoInput(sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Up)
{
    window.setFramerateLimit(60); // 60 FPS

    ground.setSize(sf::Vector2f(768.f,50.f));
    ground.setFillColor(sf::Color(100, 70, 40));
    ground.setPosition(0.f, 550.f);
}

// Game loop
void Game::run()
{
    while(window.isOpen())
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
    while(window.pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
            window.close();
    }
}

void Game::update() 
{   
    float dt = clock.restart().asSeconds();

    updatePlayer(playerOne, playerOneInput, dt);
    updatePlayer(playerTwo, playerTwoInput, dt);
}

void Game::render() 
{
    window.clear(sf::Color(50, 50, 50));
    playerOne.draw(window);
    playerTwo.draw(window);
    window.draw(ground);
    window.display();
}

void Game::updatePlayer(Player& player, const InputHandler& inputHandler, float dt)
{
    if (inputHandler.isLeftPressed())  player.moveLeft(dt);
    if (inputHandler.isRightPressed()) player.moveRight(dt);
    if (inputHandler.isJumpPressed())  player.jump();

    player.applyGravity(dt);

    if (player.isOnGround(ground))
    {
        player.stopFalling(ground);
    }
}
