#ifndef GAMEOBJECTS_H
#define GAMEOBJECTS_H

#include "GameObject"

// We make place for maxGameObjects in our gameObjects array
extern const unsigned int maxGameObjects;

// Counter of how many gameObjects are live.
extern unsigned int numGameObjects;

// Array storing all gameObjects in game
extern GameObject gameObjects[];

#endif //GAMEOBJECTS_H