#include "player.h"

Player::Player()
{
    m_speed = START_SPEED;
    m_health = START_HEALTH;
    m_maxHealth = START_HEALTH;

    m_texture.loadFromFile("src/gfx/player.png");
    m_sprite.setTexture(m_texture);
    m_sprite.setOrigin(25, 25);
}

void Player::spawn(sf::IntRect arena, sf::Vector2f resolution, int tileSize)
{
    m_position.x = arena.width / 2;
    m_position.y = arena.height / 2;

    m_arena.left = arena.left;
    m_arena.width = arena.width;
    m_arena.top = arena.top;
    m_arena.height = arena.height;

    m_tileSize = tileSize;

    //Store the resolution for future use
    m_resolution.x = resolution.x;
    m_resolution.y = resolution.y;
}

void Player::resetPlayerStats()
{
    m_speed = START_SPEED;
    m_health = START_HEALTH;
    m_maxHealth = START_HEALTH;
}

sf::Time Player::getLastHitTime()
{
    return m_LastHit;
}

bool Player::hit(sf::Time timeHit)
{
    if (timeHit.asMilliseconds() - m_LastHit.asMilliseconds() > 200)
    {
        m_LastHit = timeHit;
        m_health -= 10;
        return true;
    }
    else
    {
        return false;
    }
}

sf::FloatRect Player::getPosition()
{
    return m_sprite.getGlobalBounds();
}
sf::Vector2f Player::getCenter()
{
    return m_position;
}

float Player::getRotation()
{
    return m_sprite.getRotation();
}

sf::Sprite Player::getSprite()
{
    return m_sprite;
}

int Player::getHealth()
{
    return m_health;
}

void Player::moveLeft()
{
    m_LeftPressed = true;
}
void Player::moveRight()
{
    m_RightPressed = true;
}
void Player::moveUp()
{
    m_UpPressesed = true;
}
void Player::moveDown(){
    m_DownPressed = true;
}