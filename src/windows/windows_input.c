#ifdef WINDOWS
#include "SDL.h"
#include "keycodes.h"

int getKeyDown(unsigned char keyCode)
{
	SDL_PumpEvents();
	const Uint8* state = SDL_GetKeyboardState(NULL);
	
	if (keyCode == KEYCODE_RIGHT)
	{
		return state[SDL_SCANCODE_RIGHT];
	}
	if (keyCode == KEYCODE_LEFT)
	{
		return state[SDL_SCANCODE_LEFT];
	}
	if (keyCode == KEYCODE_DOWN)
	{
		return state[SDL_SCANCODE_DOWN];
	}
	if (keyCode == KEYCODE_UP)
	{
		return state[SDL_SCANCODE_UP];
	}
	/*
	switch (keyCode)
	{
		case KEYCODE_RIGHT:
			return state[SDL_SCANCODE_RIGHT];
	}
	*/
	return 0;
}
#endif //WINDOWS