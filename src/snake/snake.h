#ifndef SNAKE_H
#define SNAKE_H

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

void initSnake(Snake* snake);

#endif