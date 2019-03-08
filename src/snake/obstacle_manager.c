#include "obstacle.h"
#include "player.h"
#include "graphics.h"
#include "asciidisplay.h"
#include "obstacle_manager.h"
#include "rng.h"

void spawnObstacle(int x)
{
    //min 16 max 36
    //int hight = rand() % 20 + 16;
	//int hight = 16;
	int height = genRandomNum() % 20 + 16;
    
    createObstacle(x, height);
}

void obstaclesRender()
{
    for(int i=0; i<numObstacles; ++i)
    {
        obstacles[i].render(&obstacles[i]);
    }
}

void updateObstacles(Player* player)
{
	for(int i=0; i<numObstacles; ++i)
    {
		if (obstacles[i].xPos < player->xPos - 15 )
		{
			int height = genRandomNum() % 20 + 16;
			obstacles[i].height = height;
			obstacles[i].xPos += 128;
		}
			
        obstacles[i].update(&obstacles[i], player);
		
    }
}

void spawnInitialObstacles()
{
	// create 2 obstacles
	for (int i = 1; i < 3; i++)
	{
		spawnObstacle(i * 64);
	}
}