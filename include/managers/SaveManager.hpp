#pragma once
#include <string>

class SaveManager
{
public:
    static void save(int unlockedLevels);
    static int load(); // returns unlockedLevels, if file does not exist returns - 1
};