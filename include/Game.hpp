#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.hpp"
#include "InputHandler.hpp"
#include "CollisionManager.hpp"

class Game 
{
public:
    Game();
    void run();

private:
    void processEvents();
    void update();
    void render();

    sf::Clock clock;
    sf::RenderWindow window;
    sf::RectangleShape ground;
    
    std::vector<sf::RectangleShape> platforms;

    Player player;
    InputHandler input;
    CollisionManager collision;
};