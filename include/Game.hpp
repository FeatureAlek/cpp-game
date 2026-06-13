#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Player.hpp"
#include "InputHandler.hpp"
#include "CollisionManager.hpp"
#include "Platform.hpp"
#include "Hazard.hpp"
#include "Gem.hpp"
#include "Door.hpp"
#include "UI.hpp"
#include "SoundManager.hpp"
#include "TextureManager.hpp"

enum class GameState
{
    MainMenu,
    LevelSelect,
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
    void loadLevel(int levelIndex);
    
    bool allGemsCollected();

private:
    void processEvents();
    void update();
    void render();
    void updatePlayer(Player& player, const InputHandler& inputHandler, float dt);
    
    void setupBackground();
    void setupMenuBackground();

    int currentLevel = 0;

    UI ui;

    float doorTimer = 0.f;

    sf::Clock clock;
    sf::RenderWindow window;
    sf::RectangleShape background;
    sf::RectangleShape menuBackground;
    
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
