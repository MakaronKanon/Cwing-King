#include "obstacle.h"
#include "snake.h"
#include "graphics.h"
#include "asciidisplay.h"
#include "obsticalManager.h"
//#include <stdlib.h>
#include "rng.h"

void spawnObstical(int x)
{
    //min 16 max 36
    //int hight = rand() % 20 + 16;
	//int hight = 16;
	int hight = genRandomNum() % 20 + 16;
    
    createObstecle(x, hight);
}

void obstaclesRender()
{
    for(int i=0; i<nObsticals; ++i)
    {
        obsticals[i].render(&obsticals[i]);
    }
}

void updateObstacles(Snake* snake)
{
	for(int i=0; i<nObsticals; ++i)
    {
		if (obsticals[i].xPos < snake->xPos )
			obsticals[i].xPos += 128;
        obsticals[i].update(&obsticals[i], snake);
		
    }
}

void spawnInitialObstacles()
{
	// create 5 obstacles
	for (int i = 1; i < 6; i++)
	{
		spawnObstical(i * 50);
	}
}