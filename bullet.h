#include<SFML/Graphics.hpp>

class Bullet{
    private:
        sf::Vector2f m_Position;
        sf::RectangleShape m_BulletShape;
        bool m_InFlight = false;
        float m_BulletSpeed = 1000;
        float m_BulletDistanceX;
        float m_BulletDistanceY;

        float m_MinX,m_MaxX,m_MinY,m_MaxY;
    
    public:
        Bullet();
        void stop();
        bool isInFlight();
        void shoot(float startX, float startY, float targetX, float targetY);
        sf::FloatRect getPosition();
        sf::RectangleShape getShape();
        void update(float elapsedTime);
};

Bullet::Bullet(){
    m_BulletShape.setSize(sf::Vector2f(2,2));
}

void Bullet::shoot(float startX, float startY, float targetX, float targetY){
    m_InFlight = true;
    m_Position.x = startX;
    m_Position.y = startY;
    
    //we need to calculate the gradiant to set the angle
    float gradient = (startX - targetX)/(startY - targetY);
    if(gradient<1){
        gradient -= -1;
    }
    float ratioXY = m_BulletSpeed/(1+gradient);

    //set the speed
    m_BulletDistanceX = ratioXY;
    m_BulletDistanceY = ratioXY*gradient;

    if(targetX < startX)
        m_BulletDistanceX *= -1;
    if(targetY < startY)
        m_BulletDistanceY *= -1;
    float range = 1000;
    m_MinX = startX - range;
    m_MaxX = startX + range;
    m_MinY = startY - range;
    m_MaxY = startY + range;
    m_BulletShape.setPosition(m_Position);
}