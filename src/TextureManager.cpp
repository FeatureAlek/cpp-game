#include "TextureManager.hpp"

TextureManager& TextureManager::getInstance()
{
    static TextureManager instance;
    return instance;
}

sf::Texture* TextureManager::get(const std::string& filename)
{
    auto it = textures.find(filename);
    if (it != textures.end())
        return &it->second;

    sf::Texture texture;
    if (!texture.loadFromFile(std::string(GAME_ASSET_DIR) + "/textures/" + filename))
        return nullptr;

    texture.setRepeated(true);
    textures[filename] = std::move(texture);
    return &textures[filename];
}