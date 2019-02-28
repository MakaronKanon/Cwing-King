#ifdef WINDOWS

#include "stdio.h"
#include "delay.h"

void platform_init()
{
	printf("Welcome to Cwing King!\n");
	delayMilliSecs(1000);
}
#endif