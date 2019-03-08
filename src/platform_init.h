#ifndef PLATFORM_INIT_H
#define PLATFORM_INIT_H

// Crossplatform: methods needs to be implemented for every platform (Windows/MD407)

// Does initialization needed for the specific platform
// should be called at start of application.
void platform_init();

#endif //PLATFORM_INIT_H