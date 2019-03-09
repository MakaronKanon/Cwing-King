# Cwing-King
A game designed for MD407 computer. This is a lab-exercise in a machine oriented programming course.
(See game: https://www.youtube.com/watch?v=nIm1kLnfQHo)

During development there was no access to test on the physical MD407 (with Cortex M3). Instead it could only be tested with a simulator (Eterm8) which was really slow.

Therefor this project is designed it in a way making it possible to build it directly for Windows using SDL.

How to build and run:
* Build for windows (probably works for Linux, osx... to): run the makefile with make and it should create an executable inside the windowsout directory. (probably need GCC on path)
* (You can build it for MD407 with the codelite project, but you probably don't want to)

Technlogies learnt/used:
* Communicating with physical ports.
* Writing drivers for 
    * Delay
    * Graphic Display
    * Ascii Display
    * Keyboard
* General C programming
    * Separating code in multiple c-files and h-files
    * Programming for multiple architectures
    * Handling simple sprite images
    * Simple random number generator
* Simple game logic/loop
* Writing (simple) makefiles
* Working with git using multiple branches, pull requests, issues, project board
