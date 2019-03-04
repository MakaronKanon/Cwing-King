#include "delay.h"
#include "asciidisplay.h"
#include "input.h"
#include "keycodes.h"
#include "startScreen.xbm"
#include "graphics.h"

void displayWelcomeImage()
{
	
	int width_bytes;
	if (startScreen_width % 8 == 0)
	{
		width_bytes = startScreen_width/8;
	}
	else
	{
		width_bytes = startScreen_width/8+1;
	}
	
	
	// Showing image
	for (int x = 0; x < width_bytes; x++)
	{
		for (int y = 0; y < startScreen_height; y++)
		{
			unsigned char byte = startScreen_bits[x + y * width_bytes];
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

void displaySplashScreen()
{
	
	displayAscii("Showing splashscreen.", "loading");
	
	displayWelcomeImage();
	
	delayMilliSecs(1000);
	
	displayAscii("Still splashscreen", "Press 'up' to start!");
	while(!getKeyDown(KEYCODE_UP));
	
	// Here we start now, (by returning)
	
}