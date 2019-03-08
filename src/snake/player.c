#include "player.h"

#include "graphics.h"
#include "input.h"
#include "keycodes.h"
#include "stdio.h"

Player player;

static void updateSnake(Player* player)
{	
	//todo: yDir ska accelera till en maxHastighet, när snake swingar ska hastigheten sättas till lite uppåt
	player->xDir = 1;
	//snake->yDir = 1;
	player->xPos += player->xDir;
	player->yPos += player->yDir;
	
	if (player->yDir < 1)
		player->yDir++; // accelerate down
    
    player->xDelta = player->xPos - player->xStartPos;
    
    if(player->yPos > 64) 
    {
        player->dead = 1;
    }
}

static void renderSnake(Player* player)
{
	for (int x = 0; x < player->size; x++)
	{
		for (int y = 0; y < player->size; y++)
		{
			setPixel(x + player->xPos, y + player->yPos, 1);
		}
	}
}

// This make the player fly up a bit
void bounce(Player* player)
{
	player->yDir = -3; // we have to little resolution
}

void initSnake(Player* player)
{
    player->xStartPos = 10;
	player->xPos = player->xStartPos;
	player->yPos = 10;
    player->xDelta = 0;
	
	player->xDir = 1;
	player->yDir = 1;
	player->size = 4;
	player->dead = 0;
	
	player->render = renderSnake;
	player->update = updateSnake;
}