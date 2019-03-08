#include "graphics.h"
#include "delay.h"
#include "keycodes.h"
#include "input.h"
#include "player.h"
#include "platform_init.h"
#include "platform.h"
#include "obstacle.h"
#include "asciidisplay.h"
#include "splashscreen.h"
#include "gameover_screen.h"
#include "roof.h"
#include "rope.h"
#include "obstacle_manager.h"

static void update();
static void render();
static void playonegame();

static int shouldExit = 0;

void main(void)
{	
	// One-time initializations
	platform_init();
	initGraphics();

	displayAscii("Welcome to Cwing King!", "this will be a challenge.");

	while(!shouldExit)
	{
		// Init objects before every play
		initSnake(&snake);
		initRope(&rope, &snake, &roof);
        initRoof();
		spawnInitialObstacles();

		playonegame();
	}
	
	// After before exiting, clean up
	cleanUpGraphics();
}

static void playonegame()
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
			// Show gameover screen before we jump out
			displayGameoverScreen(10);
			break;
		}
		
		update();
		render();
		displayBuffer();
		clearBuffer(); //#was not enabled on MD407

		// 30fps <==> 33ms each frame
		delayMilliSecs(33);
	}
}

static void update()
{
	// Update all objects
	snake.update(&snake);
	rope.update(&rope);
	updateObstacles(&snake);
}

static void render()
{
	// Render all objects to buffer
	snake.render(&snake);
	rope.render(&rope);
    obstaclesRender();
    renderRoof(&snake);
}
