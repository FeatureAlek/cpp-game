#pragma once
#include "GameObject.hpp"
#include "Config.hpp"

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
    float speed = Config::PLATFORM_SPEED;
    float startY = 0.f;
    float moveRange = Config::PLATFORM_MOVE_RANGE;
    int direction = 1;

    PlatformType type;
};