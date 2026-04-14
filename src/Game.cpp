#include "Game.hpp"
// for debugging 
#include <iostream>

Game::Game()
: window(sf::VideoMode(768,576), "2D Game", sf::Style::Titlebar | sf::Style::Close),
  player(350.f, 250.f, sf::Color::Green)
{
    window.setFramerateLimit(60); // 60 FPS

    ground.setSize(sf::Vector2f(768.f,50.f));
    ground.setFillColor(sf::Color(100, 70, 40));
    ground.setPosition(0.f, 550.f);
    
    // platforms init
    sf::RectangleShape p1;
    p1.setSize(sf::Vector2f(200.f, 20.f));
    p1.setFillColor(sf::Color(100, 70, 40));
    p1.setPosition(100.f, 400.f);
    platforms.push_back(p1);

    sf::RectangleShape p2;
    p2.setSize(sf::Vector2f(200.f, 20.f));
    p2.setFillColor(sf::Color(100, 70, 40));
    p2.setPosition(400.f, 300.f);
    platforms.push_back(p2);


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

    if (input.isLeftPressed())   player.moveLeft(dt);
    if (input.isRightPressed())  player.moveRight(dt);
    if (input.isJumpPressed())   player.jump();

    player.applyGravity(dt);
    collision.check(player, ground, platforms, window);

}

void Game::render() 
{
    window.clear(sf::Color(50, 50, 50));
    player.draw(window);
    window.draw(ground);

    for(auto &platform : platforms){
        window.draw(platform);
    }

    window.display();
}