#include "rope.h"
#include "snake.h"
#include "input.h"
#include "keycodes.h"
#include "graphics.h"

static void updateRope();
static void renderRope();

void initRope(Rope* rope, Snake* player)
{
	rope->update = updateRope;
	rope->render = renderRope;
	rope->active = 0;
	rope->launching = 0;
	rope->player = player;
}

static void updateRope(Rope* rope)
{
	int swingButtonIsDown = getKeyDown(KEYCODE_SWING);

	if (swingButtonIsDown && !rope->active)
	{ // Begin launch
		rope->active = 1;
		rope->launching = 1;
		rope->direction.x = 1;
		rope->direction.y = -1;
		rope->start.x = rope->player->xPos;
		rope->start.y = rope->player->yPos;
		rope->end.x = rope->player->xPos;
		rope->end.y = rope->player->yPos;
	}
	
	if (rope->active && rope->launching)
	{ // keep launching
		rope->end.x += rope->direction.x;
		rope->end.y += rope->direction.y;
		
		int collidesWithRoof = 0; // todo make something to figure out this value
		if (collidesWithRoof)
		{ // stop launching
			rope->launching = 0;
		}
	}
	
	if (rope->active)
	{ // end need to stick to player
		rope->start.x = rope->player->xPos;
		rope->start.y = rope->player->yPos;
	}
	
	//todo:
	// if active && !launching:
	// we need to transform the player forwards in a swing circular motion
	
	if (!swingButtonIsDown)
	{ // stop swinging
		rope->active = 0;
	}
}

static void renderRope(Rope* rope)
{
	if (rope->active == 0)
		return;
	// if active, render from start to end

	for (int i = 0; i < 50; i++)
	{
		int x = rope->start.x + rope->direction.x * i;
		int y = rope->start.y + rope->direction.y * i;
		setPixel(x, y, 1);
	}
	
/*
	int i = 0;
	while (rope->start.x + i < rope->end.x) // exploit that rope needs to be 45 degrees.
	{
		setPixel(rope->start.x + i, rope->start.y - i, 1);
		i++;
	}*/
	/*setPixel(rope->start.x, rope->start.y, 1);
	setPixel(rope->end.x, rope->end.y, 1);*/
}