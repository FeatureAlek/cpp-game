#pragma once
#include "GameObject.hpp"

enum class PlatformType
{
    movingVertically,
    notMoving
};

class Platform : public GameObject
{
public:
    Platform(float x, float y, float width, float height, PlatformType type);

    void update(float dt);
    PlatformType getType();

private:
    float speed = 60.f;
    float startY = 0.f;
    float moveRange = 50.f;
    int direction = 1;

    PlatformType type;
};