#include "BackgroundManager.hpp"

BackgroundManager::BackgroundManager(const sf::RenderWindow& window)
{
    setupBackground(window);
    setupMenuBackground(window);
}

void BackgroundManager::setupBackground(const sf::RenderWindow& window)
{
    background.setPosition(0.f, 0.f);
    background.setSize(sf::Vector2f(
        static_cast<float>(window.getSize().x),
        static_cast<float>(window.getSize().y)));
    background.setFillColor(sf::Color(45, 45, 45));

    sf::Texture* texture = TextureManager::getInstance().get(Config::BACKGROUND_TEXTURE);
    if (texture)
    {
        background.setTexture(texture);
        background.setTextureRect(sf::IntRect(
            0, 0,
            static_cast<int>(background.getSize().x),
            static_cast<int>(background.getSize().y)));
        background.setFillColor(sf::Color::White);
    }
}

void BackgroundManager::setupMenuBackground(const sf::RenderWindow& window)
{
    menuBackground.setPosition(0.f, 0.f);
    menuBackground.setSize(sf::Vector2f(
        static_cast<float>(window.getSize().x),
        static_cast<float>(window.getSize().y)));
    menuBackground.setFillColor(sf::Color(45, 45, 45));

    sf::Texture* texture = TextureManager::getInstance().get(Config::MENU_BACKGROUND_TEXTURE);
    if (texture)
    {
        menuBackground.setTexture(texture);
        menuBackground.setTextureRect(sf::IntRect(
            0, 0,
            static_cast<int>(menuBackground.getSize().x),
            static_cast<int>(menuBackground.getSize().y)));
        menuBackground.setFillColor(sf::Color::White);
    }
}

void BackgroundManager::draw(sf::RenderWindow& window, GameState state)
{
    if (state == GameState::MainMenu || state == GameState::LevelSelect)
        window.draw(menuBackground);
    else
        window.draw(background);
}