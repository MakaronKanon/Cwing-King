#ifndef MD407_GRAPHICS_H
#define MD407_GRAPHICS_H

void setPixel(int x, int y, int set);

// Renders to screen what is on the buffer
void displayBuffer();

void initGraphics();

void cleanUpGraphics();

void clearBuffer();

#endif //MD407_GRAPHICS_H