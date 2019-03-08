#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "player.h"

// Representation of obstacle
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

// Create a obstacle
void createObstecle(int x, int hight);

#endif //OBSTACLE_H