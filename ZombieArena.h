#include <SFML/Graphics.hpp>
#include "Zombie.h"
int createBackground(sf::VertexArray &rVA, sf::IntRect arena)
{
    //any modification to rVA
    const int TILE_SIZE = 50;
    const int TILE_TYPES = 3;
    const int VERTS_IN_QUAD = 4;

    int worldHeight = arena.height / TILE_SIZE;
    int worldWidth = arena.width / TILE_SIZE;

    //what type of primitive we want to use
    //for tile it's quads
    rVA.setPrimitiveType(sf::Quads);
    //set the size of the vertex array
    rVA.resize(worldWidth * worldHeight * VERTS_IN_QUAD);

    int currVertex = 0;

    for (int w = 0; w < worldWidth; w++)
    {
        for (int h = 0; h < worldHeight; h++)
        {
            rVA[currVertex].position = sf::Vector2f(w * TILE_SIZE, h * TILE_SIZE);
            rVA[currVertex + 1].position = sf::Vector2f((w * TILE_SIZE) + TILE_SIZE, h * TILE_SIZE);
            rVA[currVertex + 2].position = sf::Vector2f((w * TILE_SIZE) + TILE_SIZE, (h * TILE_SIZE) + TILE_SIZE);
            rVA[currVertex + 3].position = sf::Vector2f((w * TILE_SIZE), (h * TILE_SIZE) + TILE_SIZE);
            
            if (h == 0 || h == worldHeight - 1 || w == 0 || w == worldWidth-1)
            //Either grass, stone, bush or wall
            {
                rVA[currVertex].texCoords = sf::Vector2f(0, 0 + TILE_TYPES * TILE_SIZE);
                rVA[currVertex + 1].texCoords = sf::Vector2f(TILE_SIZE, 0 + TILE_TYPES * TILE_SIZE);
                rVA[currVertex + 2].texCoords = sf::Vector2f(TILE_SIZE, TILE_SIZE + TILE_TYPES * TILE_SIZE);
                rVA[currVertex + 3].texCoords = sf::Vector2f(0, TILE_SIZE + TILE_TYPES * TILE_SIZE);
            }else
            {
                srand((int)time(0)+ h*w-h);
                int mOrg = rand()%TILE_TYPES;
                int verticleOffset = mOrg*TILE_SIZE;

                rVA[currVertex].texCoords = sf::Vector2f(0,0+verticleOffset);
                rVA[currVertex+1].texCoords = sf::Vector2f(TILE_SIZE,0+verticleOffset);
                rVA[currVertex+2].texCoords = sf::Vector2f(TILE_SIZE,TILE_SIZE+verticleOffset);
                rVA[currVertex+3].texCoords = sf::Vector2f(0,TILE_SIZE+verticleOffset);
            }
            currVertex += VERTS_IN_QUAD;
        }
    }
    return TILE_SIZE;
}

Zombie* createHorde(int numZombie, sf::IntRect arena) {
        Zombie* zombies = new Zombie[numZombie];

        int maxY = arena.height - 20;
        int minY = arena.top + 20;
        int maxX = arena.width - 20;
        int minX = arena.left + 20;

        for (int i=0;i<numZombie;i++) {
            //which side the zombie should spawn
            srand((int)time(0) * i);
            int side = rand()%4;
            float x, y;
            switch (side)
            {
            case 0:
                /* left */
                x = minX;
                y = (rand()%maxY) + minY;
                break;
            case 1:
                /*Right*/
                x = maxX;
                y = (rand()%maxY) + minY;
                break;
            case 2:
                /*top*/
                x = (rand()%maxX) + minX;
                y = minY;
                break;
            case 3:
                /*bottom*/
                x = (rand()%maxX) + minX;
                y = maxY;
                break;
            }
            //which type of Zombie
            srand((int)time(0)*i*2);
            int type = rand()%3;
            zombies[i].spawn(x,y,type,i);
        }
        return zombies;
    }