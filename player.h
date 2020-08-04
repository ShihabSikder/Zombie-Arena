#include<SFML/Graphics.hpp>

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