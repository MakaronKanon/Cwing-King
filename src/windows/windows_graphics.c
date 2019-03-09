#ifdef WINDOWS

#include <stdio.h>
#include "SDL.h"

// implements graphics.h
#include "graphics.h"

// A bad dependency to have, but it is needed
// for now because we subtract all x-positions from
// player's x to make player not move out of screen.
#include "player.h"

// Screen width and height of the graphic display (pixel resolution)
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// Windows size is PIXEL_SIZE times larger than real screen
// so we can see a little better
const int PIXEL_SIZE = 4;

// Buffer, we only use 1 bit in each byte but it is easier.
// In MD407_graphics.c we use every bit the byte.
static char buffer[SCREEN_WIDTH][SCREEN_HEIGHT];

// SDL's surface and window
static SDL_Surface* screenSurface;
static SDL_Window* window;

// Create a windows and gets its screenSurface
void initGraphics()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
        printf("SDL could not initialize! SDL_ERROR: %s\n", SDL_GetError());
    }
	else
	{
        window = SDL_CreateWindow("Cwing King", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH * PIXEL_SIZE, SCREEN_HEIGHT * PIXEL_SIZE, SDL_WINDOW_SHOWN);
        if (window == NULL)
		{
            printf("Window could not be created! SDL_ERROR: %s\n", SDL_GetError());
        }
		else
		{
            screenSurface = SDL_GetWindowSurface(window);
        }
    }

}

// Free resources
void cleanUpGraphics()
{
	SDL_DestroyWindow(window);
	SDL_Quit();
}

// Put pixel on a SDL surface to be rendered
static void putPixel(SDL_Surface* surface, unsigned int x, unsigned int y, Uint32 newPixelCol)
{
    Uint32 *pixels = (Uint32*)surface->pixels;
	// We have to mirror the screen in Y, because SDL expects pixelspace in fourth quadrant and 
	// we have pixels in first quadrant screen space.
	int maxIndex = surface->w * surface->h - 1;
	int oneRow = surface->w - 1;
	int index = maxIndex - y * surface->w - oneRow + x;
	pixels[index] = newPixelCol;
}

// Set pixel to buffer, (x and y are first quadrant screen space)
void setPixel(int x, int y, int set)
{    
	// Makes player be at a fixed x-pos. Static objects will "move" left.
    x -= player.xDelta;
    
	// Catch invalid coordinates to avoid buffer-overflow
	if (x >= SCREEN_WIDTH || x < 0 || y < 0 || y >= SCREEN_HEIGHT)
	{
		return; // invalid range
	}
	buffer[x][y] = set;
}

// Display buffer to screen
void displayBuffer()
{
	for (int x = 0; x < SCREEN_WIDTH; x++)
	{
		for (int y = 0; y < SCREEN_HEIGHT; y++)
		{
			// color will be 1 or 0, we convert 1 to white and 0 to black
			char color = buffer[x][y];
			Uint32 realPixelColor;
			if (color == 0)
			{
				realPixelColor = 0xFFFFFFFF;
			}
			else
			{
				realPixelColor = 0;
			}
			// For each pixel we scale it up
			for (int pixelX = 0; pixelX < PIXEL_SIZE; pixelX++)
			{
				for (int pixelY = 0; pixelY < PIXEL_SIZE; pixelY++)
				{
					putPixel(screenSurface, x * PIXEL_SIZE + pixelX, y * PIXEL_SIZE + pixelY, realPixelColor);
				}
			}
		}
	}
	// Pixels are set on surface and SDL needs to update it
	SDL_UpdateWindowSurface(window);
}

// Clear buffer
void clearBuffer()
{
	for (int x = 0; x < SCREEN_WIDTH; x++)
	{
		for (int y = 0; y < SCREEN_HEIGHT; y++)
		{
			buffer[x][y] = 0;
		}
	}
}

#endif //WINDOWS