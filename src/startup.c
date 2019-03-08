#include "graphics.h"
#include "delay.h"
#include "keycodes.h"
#include "input.h"
#include "snake.h"
#include "platform_init.h"
#include "platform.h"
#include "obstacle.h"
#include "asciidisplay.h"
#include "splashscreen.h"
#include "gameover_screen.h"
#include "roof.h"
#include "rope.h"
#include "obsticalManager.h"

void update();
void render();
void playonegame();

Snake snake;
Rope rope; // We only one rope at once.

int shouldExit = 0;

void main(void)
{	
	platform_init();
	
	displayAscii("Welcome to Cwing King!", "this will be a challenge.");
	
	displayAscii("Before 1 sec", "delay.");
	delayMilliSecs(1000);
	displayAscii("After 1 sec", "delay");

	
	initGraphics();
//    createObstecle();

	while(!shouldExit)
	{
		initSnake(&snake);
		initRope(&rope, &snake, &roof);
        initRoof();
		spawnInitialObstacles();

		playonegame();
	}

	
	cleanUpGraphics();
}

void playonegame()
{
	//#ifdef WINDOWS //todo: remove before build to md407! :)
	displaySplashScreen();
	//#endif
	
	displayAscii("Welcome to Cwing King!", "this will be a challenge.");
	
	while (1)
	{
		/*if (platform_should_exit())
		{
			shouldExit = 1;
			break;
		}*/
		if (snake.dead)
		{
			snake.dead = 0;
			// Show gameover screen before we jump out
			displayGameoverScreen(10);
			clearBuffer(); // Clear gameOver screen image.
			break;
		}
		
		update();
		render();
		// clear old display
		displayBuffer();
		clearBuffer(); //#was not enabled on MD407

		// 30fps -> 1/30 = 33ms each frame
		//delayMilliSecs(33); // Somewhat target 30 fps.
		delayMilliSecs(60); //#was not enabled on MD407
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
