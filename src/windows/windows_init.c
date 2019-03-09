#ifdef WINDOWS

#include "stdio.h"
#include "delay.h"

// implements platform_init.h
#include "platform_init.h"

void platform_init()
{
	// Nothing of value to put here, just simulate a initialization.
	printf("Starting Cwing King on windows!\n");
	delayMilliSecs(500);
}
#endif