#ifdef WINDOWS

#include <windows.h>

void delayMilliSecs(unsigned int milliSecs)
{
	Sleep(milliSecs);
}

#endif