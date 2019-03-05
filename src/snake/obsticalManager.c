#include "obstacle.h"
#include "snake.h"
#include "graphics.h"
#include "asciidisplay.h"
#include "obsticalManager.h"
#include <stdlib.h>

void spawnObstical()
{
    //min 16 max 36
    int hight = rand() * 20 + 16;
    
    createObstecle(hight);
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
        obsticals[i].update(&obsticals[i], snake);
    }
}