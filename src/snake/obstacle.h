#include "snake.h"

typedef struct tObstacle 
{
    int xPos;   // bas position is for buttom left corner
    int yPos;
    
    int width;
    int hight;
    
    void (*update)(struct tObstacle*, Snake* snake);
    void (*render)(struct tObstacle*);
} obstacle;

extern obstacle obsticals[];
extern unsigned int nObsticals;

void updateObstacles(Snake* snake);

void createObstecle();

void obstaclesRender();