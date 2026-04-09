#include "Player.hpp"

Player::Player(float x, float y, sf::Color color)
{
    shape.setSize(sf::Vector2f(50.f,50.f));
    shape.setFillColor(color);
    shape.setPosition(x,y);
}

void Player::moveLeft(float dt)  { shape.move(-speed * dt, 0.f); }
void Player::moveRight(float dt) { shape.move( speed * dt, 0.f); }
void Player::moveUp(float dt)    { shape.move(0.f, -speed * dt); }

void Player::draw(sf::RenderWindow& window)
{
    window.draw(shape);
}