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
#include "roof.h"
#include "rope.h"

void update();
void render();
void playonegame();

Snake snake;
Rope rope; // We only one rope at once.

int shouldExit = 0;

void main(void)
{	
	platform_init();
	
	initGraphics();
    createObstecle();
    initRoof();

	while(!shouldExit)
	{
		initSnake(&snake);
		initRope(&rope, &snake);

		playonegame();
	}

	
	cleanUpGraphics();
}

void playonegame()
{
	#ifdef WINDOWS //todo: remove before build to md407! :)
	displaySplashScreen();
	#endif
	
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
	rope.update(&rope);
	updateObstacles(&snake);
}

void render()
{
	// Render to buffer
	snake.render(&snake);
	rope.render(&rope);
    obstaclesRender();
    renderRoof(&snake);
}
