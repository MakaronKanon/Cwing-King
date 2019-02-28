#include "md407_ports.h"

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