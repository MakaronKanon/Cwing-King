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
	/*
	switch (keyCode)
	{
		case KEYCODE_RIGHT:
			return state[SDL_SCANCODE_RIGHT];
	}
	*/
	return 0;
}