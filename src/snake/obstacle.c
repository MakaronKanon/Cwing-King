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

static void DetectCollision(int x, int y, obstacle* this, Snake* snake)
{
    
    if(((x <= (this->xPos + this->width)) && (x >= this->xPos)) && ((y <= this->yPos) && (y >= (this->yPos - this->hight))))
    {
		snake->dead = 1;
        //displayAscii("hit!", "");
    } 
}

static void updateObstacle(obstacle* this, Snake* snake)
{
    //the collision now happens when they overlap if you want it to happen before change here
    int corners[4][2] = {
                        {snake->xPos,snake->yPos},                              //Buttom left corner !not matching corners!
                        {snake->xPos + snake->size, snake->yPos},               //Buttom right corner
                        {snake->xPos, snake->yPos + snake->size},               //Top left corner
                        {snake->xPos+ snake->size, snake->yPos + snake->size}   //Top right corner
                        };
                        
    //checks if any of the players 4 corers overlap with the obstacle 
	for(int c=0; c<4; ++c) 
    {
        DetectCollision(corners[c][0], corners[c][1], this, snake);
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

