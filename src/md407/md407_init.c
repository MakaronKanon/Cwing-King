#include "md407_ports.h"
#include "md407_asciidisplay.h"


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

void platform_init()
{
	
	#define USBDM
	#ifdef USBDM
	
	/* starta klockor port D och E */
	*((unsigned long*) 0x40023830) = 0x18;
	/* starta klockor för SYSCFG */
	*((unsigned long*) 0x40023844) |= 0x4000;
	/* Relokera vektotabellen */
	*((unsigned long*) 0xE000ED08) = 0x2001C000;
	
	#endif
	
	// 7seg-disp port D0-7
	
	// Ställ in GPIO_MODER

    portD->moder &= 0x0000FFFF;
    portD->moder |= 0x55000000;

    portD->otyper &= 0xFFFF00FF;
    portD->otyper |= 0x00000F00;

    portD->pupdr &= 0x0000FFFF;
    portD->pupdr |= 0x00AA0000;

	// init ascii
	ascii_init();

}