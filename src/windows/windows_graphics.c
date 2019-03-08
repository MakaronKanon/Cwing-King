#ifdef WINDOWS

#include <stdio.h>
#include "SDL.h"

#include <stdbool.h>
#include "player.h"

// Screen width and height is 4 times the size of the graphic display
// each pixel is therefor 4*4 real pixels.
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

const int PIXEL_SIZE = 4;

static char buffer[SCREEN_WIDTH][SCREEN_HEIGHT];

static SDL_Surface* screenSurface;
static SDL_Window* window;

void initGraphics() {

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
    *(pixels + y * surface->w + x) = newPixelCol;
}

// Set pixel to buffer
void setPixel(int x, int y, int set)
{    
    x -= player.xDelta;
    
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
			for (int pixelX = 0; pixelX < PIXEL_SIZE; pixelX++)
			{
				for (int pixelY = 0; pixelY < PIXEL_SIZE; pixelY++)
				{
					putPixel(screenSurface, x * PIXEL_SIZE + pixelX, y * PIXEL_SIZE + pixelY, realPixelColor);
				}
			}
		}
	}
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

#endif
