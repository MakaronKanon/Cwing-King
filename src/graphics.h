/*
/**
 * @brief sets the pixel on the buffer.
 * @param x coord, 0 is most left, 127 is most right
 * @param y coord, 0 is top, 63 is bottom
 * @param set, if 1-activates pixel, if 0-deactivates the pixel
 */
 /*
void setPixel(int x, int y, int set);

extern unsigned int backBuffer[128][8];*/


#ifdef WINDOWS

#include "windows_graphics.h"

#elif MD407

#include "md407_graphics.h"

#endif