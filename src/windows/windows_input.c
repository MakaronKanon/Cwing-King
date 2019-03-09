#ifdef WINDOWS
#include "SDL.h"
#include "keycodes.h"

// Implements input.h
#include "input.h"

// This is not a scalable solution but it is fine since we
// only want a few keys.
int getKeyDown(unsigned char keyCode)
{
	// Ask SDL for keyboardState
	SDL_PumpEvents();
	const Uint8* state = SDL_GetKeyboardState(NULL);
	
	// Not using switch since keycodes are const (not macros)
	// which somewhy C doesn't allow as switch-cases.
	
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
	if (keyCode == KEYCODE_SWING)
	{
		return state[SDL_SCANCODE_SPACE];
	}
	
	return 0;
}
#endif //WINDOWS