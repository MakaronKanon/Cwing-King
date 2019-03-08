#ifdef WINDOWS

#include <stdio.h>
#include "SDL.h"

//#include "main.h"
#include <stdbool.h>
#include "player.h"

static void putPixel(SDL_Surface* surface, unsigned int x, unsigned int y, Uint32 newPixelCol);

// Screen width and height is 4 times the size of the graphic display
// each pixel is therefor 4*4 real pixels.
const int SCREEN_WIDTH = 128 * 4;
const int SCREEN_HEIGHT = 64 * 4;

static char buffer[128][64];

static SDL_Surface* screenSurface;
static SDL_Window* window;

void initGraphics() {

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_ERROR: %s\n", SDL_GetError());
    } else {
        window = SDL_CreateWindow("Cwing King", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL) {
            printf("Window could not be created! SDL_ERROR: %s\n", SDL_GetError());
        } else {
            screenSurface = SDL_GetWindowSurface(window);
/*
            bool running = true;
            while (running) {
                SDL_Event event;
                while (SDL_PollEvent(&event) != 0) {
                    if (event.type == SDL_QUIT) {
                        running = false;
                    } else if (event.button.button == SDL_BUTTON_LEFT) {
                        printf("Clicked left button\n");
                    }
                }
            }*/

            //SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
            //Uint32 *pixels = screenSurface->pixels;
/*
            for (int y = 0; y < 50; y++) {
                for (int x = 0; x < 50; x++) {
                    putPixel(screenSurface, x, y, 0xFFFFFF00);
                    //*(pixels + y * screenSurface->w + x) = 0xFFFFFF00;
                }
            }

            SDL_UpdateWindowSurface(window);
            SDL_Delay(2000);
*/

        }
    }

}


void cleanUpGraphics()
{
	// Free resources
	SDL_DestroyWindow(window);
	SDL_Quit();
}


static void putPixel(SDL_Surface* surface, unsigned int x, unsigned int y, Uint32 newPixelCol)
{
    Uint32 *pixels = (Uint32*)surface->pixels;
    *(pixels + y * surface->w + x) = newPixelCol;
}

void setPixel(int x, int y, int set)
{    
    x -= player.xDelta;
    
	if (x > 127 || x < 0 || y < 0 || y > 63)
	{
		return; // invalid range
	}
	buffer[x][y] = set;
}

void displayBuffer()
{
	for (int x = 0; x < 128; x++)
	{
		for (int y = 0; y < 64; y++)
		{
			char color = buffer[x][y];
			Uint32 realPixelColor;
			if (color == 0)
			{
				realPixelColor = 0xFFFFFFFF;
				//putPixel(screenSurface, x, y, 0xFFFFFFFF);
			}
			else
			{
				realPixelColor = 0;
				//putPixel(screenSurface, x, y, 0);
			}
			for (int pixelX = 0; pixelX < 4; pixelX++)
			{
				for (int pixelY = 0; pixelY < 4; pixelY++)
				{
					putPixel(screenSurface, x * 4 + pixelX, y * 4 + pixelY, realPixelColor);
				}
			}
		}
	}
	SDL_UpdateWindowSurface(window);
}

void clearBuffer()
{
	for (int x = 0; x < 128; x++)
	{
		for (int y = 0; y < 64; y++)
		{
			buffer[x][y] = 0;
		}
	}
}

#endif
