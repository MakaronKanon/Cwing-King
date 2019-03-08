#ifndef GRAPHICS_H
#define GRAPHICS_H

// Crossplatform: methods needs to be implemented for every platform (Windows/MD407)

// Initalizes graphics
// should be called before using any other graphic-methods.
void initGraphics();

// This method clears the buffer, 
// should be called before rendering stuff to the buffer
void clearBuffer();

// Sets a pixel on the buffer
// (We only support monochrome 128*64 display)
// X coord: 0 is most left, 127 is most right
// Y coord: 0 is top, 63 is bottom
// if set is 1 it activates the pixel else it gets deactivate
void setPixel(int x, int y, int set);

// Renders the buffer to the screen
void displayBuffer();

// Before exiting, call this to release memory
void cleanUpGraphics();

#endif // GRAPHICS_H