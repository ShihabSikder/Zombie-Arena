#include <SFML/Graphics.hpp>
#include "player.h"
#include "ZombieArena.h"
//#include "Zombie.h"
int main()
{

    TextureHolder holder;

    enum class State
    {
        PAUSED,
        LEVELING_UP,
        GAME_OVER,
        PLAYING
    };
    //Load the texture for our background


    //Starting the game with gameover state
    State state = State::GAME_OVER;

    //Get screen resulation and create SFML window
    sf::Vector2f resolution;
    resolution.x = sf::VideoMode::getDesktopMode().width;
    resolution.y = sf::VideoMode::getDesktopMode().height;

    sf::RenderWindow window(sf::VideoMode(resolution.x, resolution.y),
        "Zombie Arena", sf::Style::Fullscreen);
    window.setFramerateLimit(120);
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
    sf::VertexArray background;
    background.setPrimitiveType(sf::Quads);

    //Create the backgroundVertexArray
    sf::Texture textureBackground = TextureHolder::GetTexture("src/gfx/background_sheet.png");
    //sf::Texture textureBackground;
    //textureBackground.loadFromFile("src/gfx/background_sheet.png");

    int numZombies;
    int numZombiesAlive;

    Zombie* zombies = nullptr;


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
                arena.width = 1080;
                arena.height = 1080;
                arena.left = 0;
                arena.top = 0;
                //pass the vertex array to the function

                int tileSize = createBackground(background, arena);
                player.spawn(arena, resolution, tileSize);

                numZombies = 100;

                delete[] zombies;

                zombies = createHorde(numZombies, arena);
                numZombiesAlive = numZombies;
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
            //Loop through the zombies
            for (int i=0;i<numZombies;i++) {
                if (zombies[i].isActive()) {
                    zombies[i].update(dt.asSeconds(), playerPosition);
                }
            }
        }
        //Draw the Scene
        if (state == State::PLAYING)
        {
            window.clear();
            window.setView(mainView);
            window.draw(background, &textureBackground);
            for (int i=0;i<numZombies;i++)
                window.draw(zombies[i].getSprite());
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
    delete[] zombies;
    return 0;
}