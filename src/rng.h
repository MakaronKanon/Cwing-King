#ifndef RNG_H
#define RNG_H

// Generates a pseudo-random number.
// Dont forget modulo when used.
unsigned int genRandomNum();

// Sets the seed for the number generator
void setSeed(unsigned int newSeed);

#endif //RNG_H