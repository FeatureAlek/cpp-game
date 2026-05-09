#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Player.hpp"
#include "InputHandler.hpp"
#include "CollisionManager.hpp"
#include "Hazard.hpp"
#include "Gem.hpp"

class Game 
{
public:
    Game();
    void run();
    void respawn();
    void loadMap(const std::string& filename);

private:
    void processEvents();
    void update();
    void render();
    void updatePlayer(Player& player, const InputHandler& inputHandler, float dt);

    sf::Clock clock;
    sf::RenderWindow window;
    sf::RectangleShape ground;
    
    std::vector<Hazard> hazards;
    std::vector<Platform> platforms;
    std::vector<Gem> gems;

    Player playerOne;
    Player playerTwo;
    std::vector<Player*> players;
    InputHandler playerOneInput;
    InputHandler playerTwoInput;
    CollisionManager collision;
};
