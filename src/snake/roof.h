#ifndef ROOF_H
#define ROOF_H
#include "snake.h"

// Represents a roof
typedef struct tRoof
{
    int xPos;
    int yPos;
    
    
    int width;
    int hight;
    
    void (*update)(struct tRoof* roof);
    void (*render)(Snake* snake);
} Roof;

// The roof variable
extern Roof roof;

// Initalize the roof to default values
void initRoof();

// Renders the roof
void renderRoof(Snake* snake);

#endif