#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Player.hpp"
#include "InputHandler.hpp"
#include "CollisionManager.hpp"
#include "Hazard.hpp"
#include "Gem.hpp"
#include "Door.hpp"
#include "UI.hpp"
#include "SoundManager.hpp"

enum class GameState
{
    MainMenu,
    Playing,
    Paused,
    Win,
    Lose
};

class Game 
{
public:
    Game();
    void run();
    void restart();
    void loadMap(const std::string& filename);
    
    bool allGemsCollected();

private:
    void processEvents();
    void update();
    void render();
    void updatePlayer(Player& player, const InputHandler& inputHandler, float dt);

    UI ui;

    float doorTimer = 0.f;

    sf::Clock clock;
    sf::RenderWindow window;
    sf::RectangleShape ground;
    
    std::vector<Hazard> hazards;
    std::vector<Platform> platforms;
    std::vector<Gem> gems;
    std::vector<Door> doors;

    Player playerOne;
    Player playerTwo;
    std::vector<Player*> players;
    InputHandler playerOneInput;
    InputHandler playerTwoInput;
    CollisionManager collision;

    GameState gameState = GameState::MainMenu;

    SoundManager sounds;
};
