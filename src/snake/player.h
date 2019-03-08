#ifndef SNAKE_H
#define SNAKE_H

// Represents the snake
typedef struct tSnake
{
	int xDir;
	int yDir;
	int xPos;
	int yPos;
	
	
    
    int xStartPos;
    int xDelta;
	
	int size;
	
	void (*update)(struct tSnake* snake);
	void (*render)(struct tSnake* snake);
	
	int dead;
	
} Snake;

extern Snake snake;

// Sets a snake to default values
void initSnake(Snake* snake);

// Makes snake bounce
void bounce(Snake* snake);

#endif