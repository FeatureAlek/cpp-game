#include "InputHandler.hpp"

bool InputHandler::isLeftPressed() {
    return sf::Keyboard::isKeyPressed(sf::Keyboard::A);
}
bool InputHandler::isRightPressed() {
    return sf::Keyboard::isKeyPressed(sf::Keyboard::D);
}