#ifdef WINDOWS

#include "stdio.h"
#include "delay.h"

void platform_init()
{
	printf("Starting Cwing King on windows!\n");
	delayMilliSecs(500);
}
#endif