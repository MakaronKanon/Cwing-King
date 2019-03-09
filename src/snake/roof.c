#include "roof.h"
#include "graphics.h"

Roof roof;

void renderRoof(Player* snake)
{
    int xOffset = snake->xDelta;
    roof.xPos = xOffset;
    for(int h = 0; h < roof.height; h++) 
    {
        for(int w = 0; w < roof.width; w++) 
        {
            setPixel(roof.xPos + w, roof.yPos + h, 1);
        }
    }
}

void initRoof()
{
    roof.xPos = 0;
    roof.yPos = 64-4;
    roof.height = 4;
    roof.width = 128;

    roof.render = renderRoof;
}