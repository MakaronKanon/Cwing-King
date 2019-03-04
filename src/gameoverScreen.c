#include "delay.h"
#include "asciidisplay.h"
#include "input.h"
#include "keycodes.h"
#include "Gameover.xbm"
#include "graphics.h"

//todo: this is copied from splashScreen, we shall not copy.
void displayGameoverImage()
{
	
	int width_bytes;
	if (Gameover_width % 8 == 0)
	{
		width_bytes = Gameover_width/8;
	}
	else
	{
		width_bytes = Gameover_width/8+1;
	}
	
	
	// Showing image
	for (int x = 0; x < width_bytes; x++)
	{
		for (int y = 0; y < Gameover_height; y++)
		{
			unsigned char byte = Gameover_bits[x + y * width_bytes];
			for (int k = 0; k < 8; k++)
			{
				if (byte & (1 << k))
				{
					setPixel(8 * x + k, y, 1);
				}
			}
		}
	}
	displayBuffer();
		//clearBuffer();
}


void displayGameoverScreen(int score)
{
	displayAscii("Score: xx", "nice try tho."); //todo: how can we print score?
	
	displayGameoverImage();
	
	delayMilliSecs(1000);
	displayAscii("Score: xx", "'up' to restart"); //todo: how can we print score?
	
	//displayAscii("Still splashscreen", "Press 'up' to start!");
	while(!getKeyDown(KEYCODE_UP));
	
	// Here we start now, (by returning)
}