#ifndef ROOF_H
#define ROOF_H
#include "snake.h"


typedef struct tRoof
{
    int xPos;
    int yPos;
    
    int width;
    int hight;
    
    void (*update)(struct tRoof* roof);
    void (*render)(Snake* snake);
} Roof;

void initRoof();
void renderRoof(Snake* snake);

#endif