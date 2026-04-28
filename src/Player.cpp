#include "Player.hpp"

Player::Player(float x, float y, sf::Color color)
{
    shape.setSize(sf::Vector2f(50.f,50.f));
    shape.setFillColor(color);
    shape.setPosition(x,y);

    // save spawn position
    spawnX = x;
    spawnY = y;

}

void Player::moveLeft(float dt)  { shape.move(-speed * dt, 0.f); }
void Player::moveRight(float dt) { shape.move( speed * dt, 0.f); }

void Player::draw(sf::RenderWindow& window)
{
    window.draw(shape);
}

void Player::applyGravity(float dt)
{
    velocityY += gravity * dt;
    shape.move(0.f, velocityY * dt);
}

bool Player::isOnGround(const sf::RectangleShape& ground)
{
    return shape.getGlobalBounds().intersects(ground.getGlobalBounds());
}

void Player::stopFalling(const sf::RectangleShape& ground)
{
    velocityY = 0.f;
    onGround = true;
    float groundTop = ground.getPosition().y;
    float playerHeight = shape.getSize().y;
    shape.setPosition(shape.getPosition().x, groundTop - playerHeight);
}

void Player::jump(){
    if(onGround){
        velocityY = -500.0f;
        onGround = false;
    }
}

sf::FloatRect Player::getBounds()
{
    return shape.getGlobalBounds();
}
// setters

void Player::setPositionX(float x)
{
    shape.setPosition(x, shape.getPosition().y);
}

void Player::setPositionY(float y)
{
    shape.setPosition(shape.getPosition().x, y);
}

void Player::setVelocityX(float v)
{
    velocityX = v;
}

void Player::setVelocityY(float v)
{
    velocityY = v;
}

void Player::setOnGround(bool v)
{
    onGround = v;
}

bool Player::canTouch(HazardType type) const
{
    return allowedHazards.find(type) != allowedHazards.end();
}

void Player::addAllowed(HazardType type)
{
    allowedHazards.insert(type);
}

void Player::respawn(){

    shape.setPosition(spawnX, spawnY);
    velocityX = 0.f;
    velocityY = 0.f;
}