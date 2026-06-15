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
#include "BackgroundManager.hpp"
#include "GameState.hpp"
#include "Button.hpp"
#include "SaveManager.hpp"

class Game 
{
public:
    Game();
    void run();
    void loadLevel(int levelIndex);

private:

    // unlocked levels by default 
    int unlockedLevels = 1;

    // handlers
    void handleMainMenuInput(sf::Keyboard::Key key);
    void handleInstructionsInput(sf::Keyboard::Key key);
    void handleLevelSelectInput(sf::Keyboard::Key key);
    void handlePlayingInput(sf::Keyboard::Key key);
    void handlePausedInput(sf::Keyboard::Key key);
    void handleWinInput(sf::Keyboard::Key key);
    void handleLoseInput(sf::Keyboard::Key key);
    void processEvents();
    
    // update
    void updatePlatforms(float dt);
    void updatePlayer(Player& player, const InputHandler& inputHandler, float dt);
    void updatePlayers(float dt);
    bool updateHazards();      // true if game state = Lose
    void updateGems();
    void updateDoors(float dt);
    void update();
    void updateButtons();

    // other
    void render();
    void restart();
    bool allGemsCollected();
    void loadMap(const std::string& filename);

    // window & state
    sf::RenderWindow window;
    sf::Clock clock;
    GameState gameState = GameState::MainMenu;
    float doorTimer = 0.f;
    int currentLevel = 0;

    // players
    Player playerOne;
    Player playerTwo;
    std::vector<Player*> players;
    InputHandler playerOneInput;
    InputHandler playerTwoInput;

    // world
    std::vector<Platform> platforms;
    std::vector<Hazard> hazards;
    std::vector<Gem> gems;
    std::vector<Door> doors;
    std::vector<Button> buttons;

    // managers
    CollisionManager collision;
    SoundManager sounds;
    BackgroundManager bgManager;
    UI ui;

};
