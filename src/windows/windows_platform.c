#ifdef WINDOWS

// implements platform.h
#include "platform.h"

#include "SDL.h"

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