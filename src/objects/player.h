#ifndef SNAKE_H
#define SNAKE_H

// Represents the snake
typedef struct tPlayer
{
	int xDir;
	int yDir;
	int xPos;
	int yPos;
	
	
    
    int xStartPos;
    int xDelta;
	
	int size;
	
	void (*update)(struct tPlayer* player);
	void (*render)(struct tPlayer* player);
	
	int dead;
	
} Player;

extern Player player;

// Sets a snake to default values
void initPlayer(Player* player);

// Makes snake bounce
void bounce(Player* player);

#endif