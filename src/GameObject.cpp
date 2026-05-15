#include "GameObject.hpp"
#include "TextureManager.hpp"

void GameObject::draw(sf::RenderWindow& window)
{
    window.draw(shape);
}

sf::FloatRect GameObject::getBounds()
{
    return shape.getGlobalBounds();
}

void GameObject::applyTexture(const std::string& textureFile)
{
    sf::Texture* texture = TextureManager::getInstance().get(textureFile);
    if (texture)
    {
        shape.setTexture(texture);
        shape.setTextureRect(sf::IntRect(0, 0,
            static_cast<int>(shape.getSize().x),
            static_cast<int>(shape.getSize().y)));
        shape.setFillColor(sf::Color::White);
    }
}