#pragma once
#include "GameObject.hpp"

enum class GemType
{
    redGem,
    blueGem
};

class Gem : public GameObject
{
public:
    Gem(float x, float y, float width, float height, GemType type);

    GemType getType();
    bool isCollected() const;
    void collect();

private:
    GemType type;
    bool collected = false;
};