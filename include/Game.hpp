#pragma once
#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "InputHandler.hpp"

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
    Player player;
    InputHandler input;
};