#pragma once
#include <SFML/Graphics.hpp>

class InputHandler
{
public:
    InputHandler(sf::Keyboard::Key leftKey, sf::Keyboard::Key rightKey, sf::Keyboard::Key jumpKey);

    bool isLeftPressed() const;
    bool isRightPressed() const;
    bool isJumpPressed() const;

private:
    sf::Keyboard::Key leftKey;
    sf::Keyboard::Key rightKey;
    sf::Keyboard::Key jumpKey;
};
