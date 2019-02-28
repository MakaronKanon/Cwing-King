#include "graphics.h"
#include "delay.h"
#include "keycodes.h"
#include "input.h"
#include "snake.h"
#include "platform_init.h"
#include "platform.h"

void update();
void render();

Snake snake;

void main(void)
{	
	platform_init();
	
	initSnake(&snake);
	initGraphics();
		
	while (1)
	{
		if (platform_should_exit())
		{
			break;
		}
		
		update();
		render();
		displayBuffer();
		clearBuffer();

		// 30fps -> 1/30 = 33ms each frame
		delayMilliSecs(33); // Somewhat target 30 fps.
	}

	
	cleanUpGraphics();
}

void update()
{
	// The update loop
	snake.update(&snake);
}

void render()
{
	// Render to buffer
	snake.render(&snake);
}