#ifndef OBSTACLE_MANAGER_H
#define OBSTACLE_MANAGER_H

#include "player.h"

// Update obstacles state
void updateObstacles(Player* player);

// Render the obstacles
void renderObstacles();

// Spawn initial obstacles
void initObstacles();

#endif //OBSTACLE_MANAGER_H