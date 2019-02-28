#include "md407_ports.h"


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

#define GPIO_D_BASE (0x40020C00)
typedef volatile unsigned int portType;
#define portD ((portType*) GPIO_D_BASE)

void platform_init()
{
	// We probably don't need below code, but we might want to initalize something else in future.
	
	// 7seg-disp port D0-7
	
	// Ställ in GPIO_MODER
	*portD &= 0xFFFF0000;
	*portD |= 0x00005555;
}