#pragma once
#include "GameObject.hpp"

enum class HazardType
{
    playerOneRiver,
    playerTwoRiver,
    generalRiver
};

class Hazard : public GameObject
{
public:
    Hazard(float x, float y, float width, float height, HazardType type);
    HazardType getType();

private:
    HazardType type;
};