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
#define GPIO_D_BASE (0x40020C00)
typedef volatile unsigned int portType;
#define portD ((portType*) GPIO_D_BASE)
#endif

#ifdef MD407

void init_app()
{
	// 7seg-disp port D0-7
		
	// Ställ in GPIO_MODER
	*portD &= 0xFFFF0000;
	*portD |= 0x00005555;
}


unsigned char binCodes[16] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x67, 0x77, 0x7C, 0x58, 0x5E, 0x79, 0x71};
void out7seg(unsigned char c) {
	unsigned char toWrite = 0;
	if (c >= 0 && c <= 15) {
		toWrite = binCodes[c];
	}
	
	*(portD + 5) &= 0xFFFFFF00;
	*(portD + 5) |= toWrite; // skrive en char, alltså bara de 8 lägsta bitarna
}

#endif

#include "graphics.h"
#include "delay.h"
#include "keycodes.h"
#include "input.h"

void main(void)
{	
	initGraphics();
	
	for (int x = 0; x < 128; x++)
	{
		setPixel(x, 30, 1);
	}
	displayBuffer();

	delayMilliSecs(1000);
	
	for (int x = 0; x < 128; x++)
	{
		setPixel(x, 30, 0);
	}
	
	displayBuffer();
	delayMilliSecs(1000);
	
	while (!getKeyDown(KEYCODE_RIGHT))
	{
		
	}

	
	cleanUpGraphics();
	
	
		
	/*
	// Our game loop
	while (true)
	{
		
		// 30fps -> 1/30 = 33ms each frame
		delayMilliSecs(33); // Somewhat target 30 fps.
	}*/
	
	
	#ifdef WINDOWS
	printf("Hej världen\n");
	delayMilliSecs(1000);
	#endif
	
	#ifdef MD407
	init_app();
	out7seg(5);
	#endif
}

