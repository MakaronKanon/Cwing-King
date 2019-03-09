#include "player.h"

#include "graphics.h"
#include "input.h"
#include "keycodes.h"
#include "stdio.h"

Player player;

static void updatePlayer(Player* player)
{	
	player->xPos += player->xDir;
	player->yPos += player->yDir;
	
	if (player->yDir > -1)
		player->yDir--; // accelerate down
    
	// Calculate delta so other objects can position accordingly
    player->xDelta = player->xPos - player->xStartPos;
    
    if(player->yPos < 0) 
    {
        player->dead = 1;
    }
}

static void renderPlayer(Player* player)
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
	player->yDir = 3; // we have to little resolution
}

void initPlayer(Player* player)
{
    player->xStartPos = 10;
	player->xPos = player->xStartPos;
	player->yPos = 40;
    player->xDelta = 0;
	
	player->xDir = 1;
	player->yDir = -1;
	player->size = 4;
	player->dead = 0;
	
	player->render = renderPlayer;
	player->update = updatePlayer;
}