#ifndef ROPE_H
#define ROPE_H

#include "player.h"
#include "vec2i.h"

#include "roof.h"



// Represents a rope
typedef struct tRope
{
	vec2i start; // Start point (should be were player is at)
	vec2i end; // Where to draw line to
	Player* player; // Pointer to player so we can get i's pos
	Roof* roof;
	int active; // Bool: Active only when user holds 'swing'-button, else does not render
	double angle; // angle from endpoint
	
	int lenSqr; // length of rope squared
	
	void (*render)(struct tRope* rope); // We need to render our rope sometimes
	void (*update)(struct tRope* rope); // We need to update state based on actions and last state
	
	
} Rope;

extern Rope rope;

// Sets the rope to default values
void initRope(Rope* rope, Player* player, Roof* roof);


#endif //ROPE_H