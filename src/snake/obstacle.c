#include <obstacle.h>
#include "snake.h"
#include "graphics.h"
#include "asciidisplay.h"

obstacle obstacles[10];
unsigned int nObsticals = 0;

static void render(obstacle *this)
{
    int h = 0;
    for(;h<this->hight; ++h) 
    {
        for(int w=0; w<this->width; ++w) 
        {
            setPixel(this->xPos+w,this->yPos-h,1);   
        }
    }

}

static void DetectCollision(int x, int y, obstacle* this)
{
    
    if(((x <= (this->xPos + this->width)) && (x >= this->xPos)) && ((y <= this->yPos) && (y >= (this->yPos - this->hight))))
    {
        displayAscii("hit!", "");
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
        DetectCollision(corners[c][0], corners[c][1], this);
    }
}

void updateObstacles(Snake* snake)
{
	for(int i=0; i<nObsticals; ++i)
    {
        obstacles[i].update(&obstacles[i], snake);
    }
}

void initObstecle(obstacle *current)
{
    //64 32 to place in middle of screen.
    current->xPos=24;
    current->yPos = 45;
    current->render = render;
	current->update = updateObstacle;
    current->width = 8;
    current->hight = 16;
} 

void createObstecle()
{
    initObstecle(&obstacles[nObsticals++]);
}

void obstaclesRender()
{
    for(int i=0; i<nObsticals; ++i)
    {
        obstacles[i].render(&obstacles[i]);
    }

}