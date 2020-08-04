#include <SFML/Graphics.hpp>
#include "player.h"

int main()
{
    enum class State
    {
        PAUSED,
        LEVELING_UP,
        GAME_OVER,
        PLAYING
    };

    //Starting the game with gameover state
    State state = State::GAME_OVER;

    //Get screen resulation and create SFML window
    sf::Vector2f resolution;
    resolution.x = sf::VideoMode::getDesktopMode().width;
    resolution.y = sf::VideoMode::getDesktopMode().height;

    sf::RenderWindow window(sf::VideoMode(resolution.x, resolution.y),
                            "Zombie Arena", sf::Style::Fullscreen);

    //VIEW for main action
    sf::View mainView(sf::FloatRect(0, 0, resolution.x, resolution.y));

    //Clock for timing Everything
    sf::Clock clock;

    //how long the player was active
    sf::Time gameTimeTotal;

    sf::Vector2f mouseWorldPosition;
    sf::Vector2i mouseScreenPosition;

    Player player;

    sf::IntRect arena;
    while (window.isOpen())
    {
        //Handle input
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            window.close();
            break;
        }
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed)
            {
                //pause while playing
                if (event.key.code == sf::Keyboard::Space &&
                    state == State::PLAYING)
                {
                    state = State::PAUSED;
                }
                //Restart while paused
                else if (event.key.code == sf::Keyboard::Space &&
                         state == State::PAUSED)
                {
                    state = State::PLAYING;
                }
                //start a new game
                else if (event.key.code == sf::Keyboard::Space &&
                         state == State::GAME_OVER)
                {
                    state = State::LEVELING_UP;
                }

                if (state == State::PLAYING)
                {
                }
            }
        } //end of poll event
        if (state == State::PLAYING)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                player.moveUp();
            else
                player.stopUp();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                player.moveDown();
            else
                player.stopDown();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                player.moveLeft();
            else
                player.stopLeft();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                player.moveRight();
            else
                player.stopRight();
        } //end of WASD controll

        //Handle Leveling UP
        if (state == State::LEVELING_UP)
        {
            if (event.key.code == sf::Keyboard::Num1)
            {
                state = State::PLAYING;
            }
            if (event.key.code == sf::Keyboard::Num2)
            {
                state = State::PLAYING;
            }
            if (event.key.code == sf::Keyboard::Num3)
            {
                state = State::PLAYING;
            }
            if (event.key.code == sf::Keyboard::Num4)
            {
                state = State::PLAYING;
            }
            if (event.key.code == sf::Keyboard::Num5)
            {
                state = State::PLAYING;
            }
            if (event.key.code == sf::Keyboard::Num6)
            {
                state = State::PLAYING;
            }
            if (state == State::PLAYING)
            {
                arena.width = 500;
                arena.height = 500;
                arena.left = 0;
                arena.top = 0;

                int tileSize = 50;
                player.spawn(arena, resolution, tileSize);
                clock.restart();
            }
        } // End of leveling UP
        //UPDATE the frame
        if (state == State::PLAYING)
        {
            sf::Time dt = clock.restart();
            gameTimeTotal += dt;
            float dtAsSec = dt.asSeconds();
            mouseScreenPosition = sf::Mouse::getPosition();
            mouseWorldPosition = window.mapPixelToCoords(sf::Mouse::getPosition(), mainView);
            //update player
            player.update(dtAsSec, sf::Mouse::getPosition());

            //make a note for players new position
            sf::Vector2f playerPosition(player.getCenter());

            //make the view center around the player
            mainView.setCenter(player.getCenter());
        }
        //Draw the Scene
        if (state == State::PLAYING)
        {
            window.clear();
            window.setView(mainView);
            window.draw(player.getSprite());
        }
        if (state == State::LEVELING_UP)
        {
        }
        if (state == State::GAME_OVER)
        {
        }
        if (state == State::PAUSED)
        {
        }
        window.display();
    }
    return 0;
}