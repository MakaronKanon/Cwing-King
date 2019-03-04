#ifndef ROPE_H
#define ROPE_H

#include "snake.h"
#include "vec2i.h"
#include "roof.h"


typedef struct tRope
{
	vec2i start; // Start point (should be were player is at)
	vec2i end; // Where to draw line to
	vec2i direction; // Which direction is the rope (end) traveling
	Snake* player; // Pointer to player so we can get i's pos
	Roof* roof;
	int active; // Bool: Active only when user holds 'swing'-button, else does not render
	
	int lenSqr; // length of rope squared
	
	void (*render)(struct tRope* rope); // We need to render our rope sometimes
	void (*update)(struct tRope* rope); // We need to update state based on actions and last state
	
	
} Rope;

void initRope(Rope* rope, Snake* player, Roof* roof);


#endif //ROPE_H