#include "InputHandler.hpp"

InputHandler::InputHandler(sf::Keyboard::Key leftKey, sf::Keyboard::Key rightKey, sf::Keyboard::Key jumpKey)
    : leftKey(leftKey), rightKey(rightKey), jumpKey(jumpKey)
{
}

bool InputHandler::isLeftPressed() const
{
    return sf::Keyboard::isKeyPressed(leftKey);
}

bool InputHandler::isRightPressed() const
{
    return sf::Keyboard::isKeyPressed(rightKey);
}

bool InputHandler::isJumpPressed() const
{
    return sf::Keyboard::isKeyPressed(jumpKey);
}
