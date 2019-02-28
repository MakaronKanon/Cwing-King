/*
 * 	startup.c
 *
 */
 
 #ifndef WINDOWS
void startup(void) __attribute__((naked)) __attribute__((section (".start_section")) );

void startup ( void )
{
__asm volatile(
	" LDR R0,=0x2001C000\n"		/* set stack */
	" MOV SP,R0\n"
	" BL main\n"				/* call main */
	"_exit: B .\n"				/* never return */
	) ;
}

#endif

#ifdef WINDOWS
#include "stdio.h"
#endif



#ifdef MD407

/*
void init_app()
{
	// 7seg-disp port D0-7
		
	// Ställ in GPIO_MODER
	*portD &= 0xFFFF0000;
	*portD |= 0x00005555;
}*/

#endif

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
		clearBuffer();
		render();
		displayBuffer();
		
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