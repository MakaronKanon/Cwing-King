#ifdef WINDOWS

#include "stdio.h"

// Implements asciidisplay.h
#include "asciidisplay.h" 

// Emulates ascii display using terminal
void displayAscii(char* line1, char* line2)
{
	// "clear screen"
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"); 
	printf(line1);
	printf("\n");
	printf(line2);
}

#endif //WINDOWS