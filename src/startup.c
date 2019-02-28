#include "graphics.h"
#include "delay.h"
#include "keycodes.h"
#include "input.h"
#include "snake.h"
#include "platform_init.h"

void update();
void render();

Snake snake;

void main(void)
{	
	platform_init();
	
	initSnake(&snake);
	initGraphics();
	
	int playing = 1;
	
	while (playing)
	{
		
		/*
		if (getKeyDown(KEYCODE_RIGHT))
		{
			playing = 0;
		}
		*/
		
		
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