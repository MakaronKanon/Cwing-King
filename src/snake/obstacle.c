#include <obstacle.h>
#include "player.h"
#include "graphics.h"
#include "asciidisplay.h"
//#include <stdio.h>

obstacle obsticals[10];
unsigned int nObsticals = 0;

static void render(obstacle *this)
{
	//printf("xpos: %d, ypos: %d \n width: %d, height: %d \n", this->xPos, this->yPos, this->width, this->hight);
    int h = 0;
    for(;h<this->hight; ++h) 
    {
        for(int w=0; w<this->width; ++w) 
        {
            setPixel(this->xPos+w,this->yPos-h,1);   
        }
    }

}

static void DetectCollision(int x, int y, obstacle* this, Player* player)
{
    
    if(((x <= (this->xPos + this->width)) && (x >= this->xPos)) && ((y <= this->yPos) && (y >= (this->yPos - this->hight))))
    {
		player->dead = 1;
        //displayAscii("hit!", "");
    } 
}

static void updateObstacle(obstacle* this, Player* player)
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
        DetectCollision(corners[c][0], corners[c][1], this, player);
    }
}


void initObstecle(obstacle *current, int hight, int x)
{
    //64 32 to place in middle of screen.
    current->xPos=x;//150;
    current->yPos = 64;
    current->render = render;
	current->update = updateObstacle;
    current->width = 8;
    current->hight = hight;
} 

void createObstecle(int x, int hight)
{
    //start over if array is full. all obstical can be on scrren in the same time
    if(nObsticals > sizeof(obsticals))
    {
        nObsticals = 0;
    }
        
    initObstecle(&obsticals[nObsticals++], hight, x);
}

