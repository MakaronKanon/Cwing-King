#include <obstacle.h>
#include "player.h"
#include "graphics.h"
#include "asciidisplay.h"

static void render(Obstacle *this)
{
    for(int h = 0; h<this->height; h++) 
    {
        for(int w = 0; w<this->width; w++) 
        {
            setPixel(this->xPos + w, this->yPos + h,1);   
        }
    }
}

static void detectCollision(int x, int y, Obstacle* this, Player* player)
{
    
    if(((x <= (this->xPos + this->width)) && (x >= this->xPos)) && ((y <= this->yPos + this->height) && (y >= this->yPos)))
    {
		player->dead = 1;
    } 
}

static void updateObstacle(Obstacle* this, Player* player)
{
    //the collision now happens when they overlap if you want it to happen before change here
    int corners[4][2] = {
                        {player->xPos,player->yPos},                              //Buttom left corner !not matching corners!
                        {player->xPos + player->size, player->yPos},               //Buttom right corner
                        {player->xPos, player->yPos + player->size},               //Top left corner
                        {player->xPos+ player->size, player->yPos + player->size}   //Top right corner
                        };
                        
    //checks if any of the players 4 corers overlap with the obstacle 
	for(int c=0; c<4; ++c) 
    {
        detectCollision(corners[c][0], corners[c][1], this, player);
    }
}


void initObstacle(Obstacle *current, int height, int x)
{
    current->xPos=x;
    current->render = render;
	current->update = updateObstacle;
    current->width = 8;
    current->height = height;
	current->yPos = 0;

} 