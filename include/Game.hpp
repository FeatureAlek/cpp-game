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
    void updatePlayer(Player& player, const InputHandler& inputHandler, float dt);

    sf::Clock clock;
    sf::RenderWindow window;
    sf::RectangleShape ground;

    Player playerOne;
    Player playerTwo;
    InputHandler playerOneInput;
    InputHandler playerTwoInput;
};
