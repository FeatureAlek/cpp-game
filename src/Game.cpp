#include "Game.hpp"

Game::Game()
: window(sf::VideoMode(800,600), "2D Game"),
  block(350,250)
{
    
}

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

}

void Game::render()
{
    window.clear();

    block.draw(window);

    window.display();
}