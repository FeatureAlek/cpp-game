#include "Game.hpp"

Game::Game()
: window(sf::VideoMode(768,576), "2D Game"),
  player(350.f, 250.f, sf::Color::Green)
{}

void Game::run()
{
    while(window.isOpen())
    {
        processEvents();
        update();
        render();
    }
}

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

    if (input.isLeftPressed())   player.moveLeft(dt);
    if (input.isRightPressed())  player.moveRight(dt);
    if (input.isUpPressed())     player.moveUp(dt);
}

void Game::render() 
{
    window.clear(sf::Color(50, 50, 50));
    player.draw(window);
    window.display();
}