#ifdef WINDOWS

// implements platform.h
#include "platform.h"

#include "SDL.h"

// This value gets polled, let SDL decide if we need to exit.
int platform_should_exit()
{
	// We need to check from SDL if we should exit.
	if (SDL_QuitRequested())
	{
		return 1;
	}
	
	return 0;
}

#endif //WINDOWS