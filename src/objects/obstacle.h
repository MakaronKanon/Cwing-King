#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "player.h"

// Representation of obstacle
typedef struct tObstacle 
{
    int xPos;   // base-position is for bottom left corner
    int yPos;
    
    int width;
    int height;
    
    void (*update)(struct tObstacle*, Player* snake);
    void (*render)(struct tObstacle*);
} Obstacle;

void initObstacle(Obstacle *current, int height, int x);


#endif //OBSTACLE_H