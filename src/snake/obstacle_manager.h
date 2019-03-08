#ifndef OBSTACLE_MANAGER_H
#define OBSTACLE_MANAGER_H

#include "player.h"

// Update obstacles state
void updateObstacles(Player* player);

// Spawn a obstacle
void spawnObstacle();

// Render the obstacles
void obstaclesRender();

// Spawn initial obstacles
void spawnInitialObstacles();

#endif //OBSTACLE_MANAGER_H