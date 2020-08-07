#include<SFML/Graphics.hpp>
#include<ctime>
#include<cstdlib>
#include<math.h>
#include "TextureHolder.h"

using namespace std;

class Zombie {
private:
    //How fast each zombie type
    const float BLOATER_SPEED = 40;
    const float CHASER_SPEED = 80;
    const float CRAWLER_SPEED = 20;

    //Health of zombie

    const float BLOATER_HEALTH = 5;
    const float CHASER_HEALTH = 1;
    const float CRAWLER_HEALTH = 3;

    //making zomibe vary speed 
    const int MAX_VARRIANCE = 30;
    const int OFFSET = 101 - MAX_VARRIANCE;

    //Where is the zombie
    sf::Vector2f m_Position;
    //sprite for zombie
    sf::Sprite m_Sprite;

    float m_Speed;
    float m_Health;

    //is it still alive?
    bool m_Active;

public:
    bool hit() {
        m_Health--;
        if (m_Health<0) {
            m_Active = false;
            m_Sprite.setTexture(TextureHolder::GetTexture("src/gfx/blood.png"));
            return true;
        }
        //Zombie has still some health
        return false;
    }
    bool isActive() {
        return m_Active;
    }
    void spawn(float startX, float startY, int type, int seed) {
        switch (type)
        {
        case 0:
            /* Bloater */
            m_Sprite = sf::Sprite(TextureHolder::GetTexture("src/gfx/bloater.png"));
            m_Speed = BLOATER_SPEED;
            m_Health = BLOATER_HEALTH;
            break;
        case 1:
            /*Chaser*/
            m_Sprite = sf::Sprite(TextureHolder::GetTexture("src/gfx/chaser.png"));
            m_Speed = CHASER_SPEED;
            m_Health = CHASER_HEALTH;
            break;
        case 2:
            m_Sprite = sf::Sprite(TextureHolder::GetTexture("src/gfx/crawler.png"));
            m_Speed = CRAWLER_SPEED;
            m_Health = CRAWLER_HEALTH;
            break;
        }
        //Modify speed
        srand((int)time(0)*seed);
        //difference between 80-100
        float modifier = (rand()%MAX_VARRIANCE) + OFFSET;
        modifier /=100;
        m_Speed *= modifier;
        m_Position.x = startX;
        m_Position.y = startY;
        m_Sprite.setOrigin(25, 25);
        m_Sprite.setPosition(m_Position);
    }
    sf::FloatRect getPosition() {
        return m_Sprite.getGlobalBounds();
    }
    sf::Sprite getSprite() {
        return m_Sprite;
    }
    void update(float elapsedTime, sf::Vector2f playerLocation) {
        float playerX = playerLocation.x;
        float playerY = playerLocation.y;

        //Update the zombie position
        if (playerX > m_Position.x)
            m_Position.x = m_Position.x + m_Speed*elapsedTime;
        if (playerY > m_Position.y)
            m_Position.y = m_Position.y + m_Speed*elapsedTime;
        if (playerX < m_Position.x)
            m_Position.x = m_Position.x - m_Speed*elapsedTime;
        if (playerY < m_Position.y)
            m_Position.y = m_Position.y - m_Speed*elapsedTime;

        m_Sprite.setPosition(m_Position);

        //Rotating the zombie to the player

        float angle = (atan2(playerY-m_Position.y, playerX-m_Position.x)*180)/3.141;
        m_Sprite.setRotation(angle);
    }
};

