#include "rope.h"
#include "snake.h"
#include "input.h"
#include "keycodes.h"
#include "graphics.h"
#include "roof.h"
#include "asciidisplay.h"
#include "math.h"
#include <stdio.h>

static void updateRope();
static void renderRope();

void initRope(Rope* rope, Snake* player, Roof* roof)
{
	rope->update = updateRope;
	rope->render = renderRope;
	rope->active = 0;
	rope->player = player;
	rope->roof = roof;
}

static int pointCollidesWithRoof(int x, int y, Roof* roof)
{
	if(((x <= (roof->xPos + roof->width)) && (x >= roof->xPos)) && ((y <= roof->yPos) && (y >= (roof->yPos - roof->hight))))
    {
		return 1;
    } 
	return 0;
}

static void updateRope(Rope* rope)
{
	int swingButtonIsDown = getKeyDown(KEYCODE_SWING);

	if (swingButtonIsDown && !rope->active)
	{ // Begin launch
		rope->active = 1;
		rope->direction.x = 1;
		rope->direction.y = -1;
		rope->start.x = rope->player->xPos;
		rope->start.y = rope->player->yPos;
		
		// while loop, som går ett steg längs direction
		// efter varje step ska den kolla om "endpoint" ligger i taket
		// ligger den i taket så är vi klara då sätter vi endpoint där
		// om vi kört 1000 steg, så är något fel och vi visar felmeddelande eller något
		int endX = rope->start.x;
		int endY = rope->start.y;
		int i = 0;
		while (++i < 1000)
		{
			endX += rope->direction.x;
			endY += rope->direction.y;
			if (pointCollidesWithRoof(endX, endY, rope->roof))
			{
				displayAscii("collision", "with roof");
				
				
				
				// we have found the roof,
				break;
			}
			if (i == 999)
			{
				// this should never happen.
			}
		}
		
		
		rope->end.x = endX;
		rope->end.y = endY;
		// we need to get length and store in rope

		double deltaX = rope->end.x - rope->start.x;
		double deltaY = rope->end.y - rope->start.y;
		double lenSqr = deltaX * deltaX + deltaY * deltaY;
		rope->lenSqr = lenSqr;
		
		//rope->end.x = rope->player->xPos;
		//rope->end.y = rope->player->yPos;
	}
	/*
	if (rope->active && rope->launching)
	{ // keep launching
		rope->end.x += rope->direction.x;
		rope->end.y += rope->direction.y;
		
		int collidesWithRoof = 0; // todo make something to figure out this value
		if (collidesWithRoof)
		{ // stop launching
			rope->launching = 0;
		}
	}*/
	
	if (rope->active)
	{ // end need to stick to player
		// player need to stick to end
		
		if (rope->player->yPos < 15)
		{
			// player need to let go to avoid bugs
			rope->active = 0;
		}
		
		// change startPos little bit
		double lenSqr = rope->lenSqr;
		double deltaX = rope->end.x - rope->start.x;
		double deltaY = rope->end.y - rope->start.y;
		deltaX -= 1; // åk åt höger
		deltaY = sqrt(-deltaX * deltaX + lenSqr);
		
		printf("playerx %d\n", rope->player->xPos);
		printf("playery %d\n", rope->player->yPos);
		printf("deltay %f\n", deltaY);
		printf("deltax %f\n", deltaX);
		
		//deltaX *= -1;
		//deltaY *= -1;
		rope->start.x = rope->end.x - deltaX ;
		rope->start.y = -rope->end.y + deltaY;
		
		rope->player->xPos = rope->start.x;
		rope->player->yPos = rope->start.y;
		
		/*
		rope->start.x = rope->player->xPos;
		rope->start.y = rope->player->yPos;*/
		
		
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
    double deltaX = rope->player->xPos - rope->end.x;
    double deltaY = -(rope->player->yPos - rope->end.y);
    
    double ang = atan(deltaY/deltaX);
    
    int x = 0;
    int y = 0;
    int l = 1;
    
//    printf("deg: %f \n",ang * 180/3.1415);
    while(rope->start.y - y > rope->end.y)
    {
        x = cos(ang) * l;
        y = sin(ang) * l;
		if (y < 0)
		{
			y = -y;
			x = -x;
		}
			
        //printf("x: %d \n",x);
        //printf("y: %d \n",y);
        setPixel(x+rope->start.x,-y+rope->start.y,1);
        l++;
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