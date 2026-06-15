#pragma once
#include "GameObject.hpp"

class Button : public GameObject
{
public:
    Button(float x, float y, float width, float height);

    void setPressed(bool pressed);
    bool isPressed() const;

private:
    bool pressed = false;
};