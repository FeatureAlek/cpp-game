#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>

class TextureManager
{
public:
    static TextureManager& getInstance();
    sf::Texture* get(const std::string& filename);

private:
    TextureManager() = default;
    std::unordered_map<std::string, sf::Texture> textures;
};