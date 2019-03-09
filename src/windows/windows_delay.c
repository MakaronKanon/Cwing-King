#ifdef WINDOWS

#include <windows.h>

// Implements delay.h
#include "delay.h"

void delayMilliSecs(unsigned int milliSecs)
{
	Sleep(milliSecs); 
}

#endif