#pragma once
#include "GameObject.hpp"
#include "Config.hpp"

enum class PlatformType
{
    movingVertically,
    notMoving,
    buttonControlled
};

class Platform : public GameObject
{
public:
    Platform(float x, float y, float width, float height, PlatformType type);

    void setActive(bool active);

    void update(float dt);
    PlatformType getType() const;

private:
    float speed = Config::PLATFORM_SPEED;
    float startY = 0.f;
    float moveRange = Config::PLATFORM_MOVE_RANGE;
    int direction = 1;

    bool active = false;

    PlatformType type;
};