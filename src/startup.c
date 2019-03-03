#include "graphics.h"
#include "delay.h"
#include "keycodes.h"
#include "input.h"
#include "snake.h"
#include "platform_init.h"
#include "platform.h"
#include "obstacle.h"
#include "asciidisplay.h"
#include "splashScreen.h"
#include "gameoverScreen.h"

void update();
void render();
void playonegame();

Snake snake;
int shouldExit = 0;

void main(void)
{	
	platform_init();
	
	initGraphics();
    createObstecle();
		
	while(!shouldExit)
	{
		initSnake(&snake);

		playonegame();
	}

	
	cleanUpGraphics();
}

void playonegame()
{
	displaySplashScreen();
	
	displayAscii("Welcome to Cwing King!", "this will be a challenge.");
	
	while (1)
	{
		if (platform_should_exit())
		{
			shouldExit = 1;
			break;
		}
		if (snake.dead)
		{
			snake.dead = 0;
			// Show gameover screen before we jump out
			displayGameoverScreen(10);
			break;
		}
		
		update();
		render();
		displayBuffer();
		clearBuffer();

		// 30fps -> 1/30 = 33ms each frame
		delayMilliSecs(33); // Somewhat target 30 fps.
		delayMilliSecs(60); //tempdelay
	}
}

void update()
{
	// The update loop
	snake.update(&snake);
	updateObstacles(&snake);
}

void render()
{
	// Render to buffer
	snake.render(&snake);
    obstaclesRender();
}
