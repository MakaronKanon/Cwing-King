#ifndef OBSTICALMANAGER_H
#define OBSTICALMANAGER_H

#include "snake.h"

// Update obstacles state
void updateObstacles(Snake* snake);

// Spawn a obstacle
void spawnObstical();

// Render the obstacles
void obstaclesRender();

// Spawn initial obstacles
void spawnInitialObstacles();

#endif