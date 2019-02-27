#include "snake.h"

#include "graphics.h"
#include "input.h"
#include "keycodes.h"

static void updateSnake(Snake* snake)
{
	// Get input
	if(getKeyDown(KEYCODE_RIGHT))
	{
		snake->xDir = 1;
	}
	else if (getKeyDown(KEYCODE_LEFT))
	{
		snake->xDir = -1;
	}
	if(getKeyDown(KEYCODE_UP))
	{
		snake->yDir = -1;
	}
	else if (getKeyDown(KEYCODE_DOWN))
	{
		snake->yDir = 1;
	}
	
	snake->xPos += snake->xDir;
	snake->yPos += snake->yDir;
}

static void renderSnake(Snake* snake)
{
	for (int x = 0; x < snake->size; x++)
	{
		for (int y = 0; y < snake->size; y++)
		{
			setPixel(x + snake->xPos, y + snake->yPos, 1);
		}
	}
}

void initSnake(Snake* snake)
{
	snake->xPos = 10;
	snake->yPos = 10;
	
	snake->xDir = 1;
	snake->yDir = 1;
	snake->size = 4;
	
	snake->render = renderSnake;
	snake->update = updateSnake;
}