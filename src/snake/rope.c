#include "rope.h"
#include "player.h"
#include "input.h"
#include "keycodes.h"
#include "graphics.h"
#include "roof.h"
#include "asciidisplay.h"
#include "math.h"

Rope rope; // We only one rope at once.

static void updateRope();
static void renderRope();

void initRope(Rope* rope, Player* player, Roof* roof)
{
	rope->update = updateRope;
	rope->render = renderRope;
	rope->active = 0;
	rope->player = player;
	rope->roof = roof;
    rope->lenSqr = 1;
	rope->angle = 0;
}

// Updates a rope
static void updateRope(Rope* rope)
{
	int swingButtonIsDown = getKeyDown(KEYCODE_SWING);

	if (swingButtonIsDown && !rope->active)
	{ // Begin launch
		rope->active = 1;
		
		// Startpos should be where player is
		rope->start.x = rope->player->xPos;
		rope->start.y = rope->player->yPos;
		
		// Endpos x should be where player is
		// Endpos y should be roofs y (shoots straight up)
		rope->end.x = rope->start.x;
		rope->end.y = rope->roof->yPos;
		rope->angle = 0;
		
		// Rope length is deltaY
		int deltaY = rope->end.y - rope->start.y;
		rope->lenSqr = deltaY * deltaY;;
	}
	
	if (rope->active)
	{ 
		int len = sqrt(rope->lenSqr);

		// Calculate swinging motion (longer rope slower angle)
		rope->angle += 60 * (3.14/180) / len; // add angle
		
		// calculate startpos based on angle
		rope->start.x = rope->end.x + sin(rope->angle) * len;
		rope->start.y = rope->end.y - cos(rope->angle) * len;
		
		// Player should stick to the rope
		rope->player->xPos = rope->start.x;
		rope->player->yPos = rope->start.y;
		
	}
	
	if (rope->active && !swingButtonIsDown)
	{ 
		// stop swinging and reset rope
		rope->active = 0;
        initRope(rope,rope->player,rope->roof);
		
		// make player jump up a little
		bounce(&player);
	}
}

// Renders a rope
static void renderRope(Rope* rope)
{
	// Don't render if rope is inactive
	if (rope->active == 0)
		return;
	
	// ang between rope direction (end to start) and vector down
    double ang = rope->angle;
	
	// use sin and cos to calculate x and y for every length < rope.length
	int rendLen = 0;
	while (rendLen * rendLen < rope->lenSqr)
	{
		int x = sin(ang) * rendLen;
		int y = cos(ang) * rendLen;
		
		// x and y are offset from end of rope (the point at the roof)
		setPixel(rope->end.x + x, rope->end.y - y, 1);
		
		rendLen++;
	}
}