#include<SFML/Graphics.hpp>
#include<math.h>
class Player{
    const float START_SPEED = 200;
    const float START_HEALTH = 100;
    
    //player position
    sf::Vector2f m_position;
    
    sf::Sprite m_sprite;
    sf::Texture m_texture;
    
    //screen resolution
    sf::Vector2f m_resolution;
    sf::IntRect m_arena;
    int m_tileSize;

    //player direction
    bool m_UpPressesed;
    bool m_DownPressed;
    bool m_LeftPressed;
    bool m_RightPressed;

    int m_health;
    int m_maxHealth;

    //When the player was hit
    sf::Time m_LastHit;
    float m_speed;

    public:
        Player();
        void spawn(sf::IntRect arena, sf::Vector2f resolution, int tileSize);
        
        //Call this end of the game
        void resetPlayerStats();
        bool hit(sf::Time timeHit);
        sf::Time getLastHitTime();
        
        //Where is the player
        sf::FloatRect getPosition();
        
        //get center of the player
        sf::Vector2f getCenter();

        //which angle the player is facing
        float getRotation();

        sf::Sprite getSprite();

        //move the player

        void moveUp();
        void moveDown();
        void moveRight();
        void moveLeft();

        //stop the player move

        void stopUp();
        void stopDown();
        void stopRight();
        void stopLeft();

        //we will update this in every frame

        void update(float elapsedTime, sf::Vector2i mousePosition);

        //speed boost
        void upgradeSpeed();
        //health boost
        void upgradeHealth();

        //increase max health
        void increaseHealthLevel(int amount);

        //how much health has the player got
        int getHealth();
};

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
void Player::moveDown()
{
    m_DownPressed = true;
}
void Player::stopLeft()
{
    m_LeftPressed = false;
}
void Player::stopRight()
{
    m_RightPressed = false;
}
void Player::stopUp()
{
    m_UpPressesed = false;
}
void Player::stopDown()
{
    m_DownPressed = false;
}

void Player::update(float elapsedTime, sf::Vector2i mousePosition){
    if(m_UpPressesed)
        m_position.y -= m_speed*elapsedTime;
    if(m_DownPressed)
        m_position.y += m_speed*elapsedTime;
    if(m_RightPressed)
        m_position.x += m_speed*elapsedTime;
    if(m_LeftPressed)
        m_position.x -= m_speed*elapsedTime;
    
    m_sprite.setPosition(m_position);

    //keeping the player in the arena

    if(m_position.x > m_arena.width - m_tileSize)
        m_position.x = m_arena.width - m_tileSize;
    
    if(m_position.x < m_arena.left + m_tileSize)
        m_position.x = m_arena.left + m_tileSize;

    if(m_position.y > m_arena.height - m_tileSize)
        m_position.y = m_arena.height - m_tileSize;
    
    if(m_position.y < m_arena.top + m_tileSize)
        m_position.y = m_arena.top + m_tileSize;
    
    //calculate the angel of the player face
    //using trigonometric fn TAN to calculate face rotation
    // tan@ = y/x to convert to radian div by pi/180
    float angle = (atan2(mousePosition.y - m_resolution.y/2,
                mousePosition.x - m_resolution.x/2)*180)/3.1416;
    m_sprite.setRotation(angle);
}

void Player::upgradeSpeed(){
    //25% speed boost
    m_speed += (START_SPEED*0.25);
}

void Player::upgradeHealth(){
    //25% of max health
    m_maxHealth += (START_HEALTH * 0.25);
}

void Player::increaseHealthLevel(int amount){
    m_health += amount;

    //putting a constraint for max health
    if(m_health>m_maxHealth)
        m_health = m_maxHealth;
}