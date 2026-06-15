#include "Button.hpp"
#include "Config.hpp"

Button::Button(float x, float y, float width, float height)
{
    shape.setSize(sf::Vector2f(width, height));
    shape.setPosition(x, y);

    applyTexture("button_unpressed.png");
}

void Button::setPressed(bool p)
{
    if (pressed == p)
        return;
        
    pressed = p;
    applyTexture(pressed ? "button_pressed.png" : "button_unpressed.png");
}

bool Button::isPressed() const { return pressed; }