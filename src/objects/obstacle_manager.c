#include "obstacle.h"
#include "player.h"
#include "graphics.h"
#include "asciidisplay.h"
#include "obstacle_manager.h"
#include "rng.h"

#define NUM_OBS 3
Obstacle obstacles[NUM_OBS];

void initObstacles()
{
	// create 2 obstacles
	for (int i = 0; i < NUM_OBS; i++)
	{
		int height = genRandomNum() % 20 + 16;
		int x = i * (128/NUM_OBS);
		initObstacle(&obstacles[i], height, x);
	}
}

void renderObstacles()
{
    for(int i=0; i<NUM_OBS; ++i)
    {
        obstacles[i].render(&obstacles[i]);
    }
}

void updateObstacles(Player* player)
{
	for(int i=0; i<NUM_OBS; ++i)
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