#include "roof.h"
#include "graphics.h"

Roof roof;

void renderRoof(Snake* snake)
{
    int xOffset = snake->xDelta;
    roof.xPos = xOffset;
    for(int h=0; h<roof.hight; ++h) 
    {
        for(int w=0; w<roof.width; ++w) 
        {
            setPixel(roof.xPos + w,roof.yPos + h,1);
        }
    }

}

void initRoof()
{
    roof.xPos = 0;
    roof.yPos = 0;
    roof.hight = 4;
    roof.width = 128;//*100; tog för lång tid?
    
    roof.render = renderRoof;
}