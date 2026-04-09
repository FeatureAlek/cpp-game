#pragma once
#include <SFML/Graphics.hpp>
#include "Block.hpp"

class Game
{
private:
    sf::RenderWindow window;
    Block block;

public:
    Game();
    void run();

private:
    void processEvents();
    void update();
    void render();
};