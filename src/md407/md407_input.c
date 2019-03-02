#ifdef MD407


// Input från portD
#include "md407_ports.h"
#include "keycodes.h"

// row should be between 0 and 3
static void activateRow(int row) {
	// är row 3 ska vi skriva till b7
	// är row 0 ska vi skriva till b4
	unsigned int bitRow = 0;
	if (row == 0) {
		bitRow = 1;
	} else if (row == 1) {
		bitRow = 2;
	} else if (row == 2) {
		bitRow = 4;
	} else if (row == 3) {
		bitRow = 8;
	}
	bitRow <<= 4; // Sätt row till rätt plats (b4 till b7 där b4 är row 0)
	bitRow <<= 8; // shifta en byte åt vänster 
	portDNew->odr &= 0xFFFF0FFF;
	portDNew->odr |= bitRow;
	//*(portD + 5) &= 0xFFFF0FFF;
	//*(portD + 5) |= bitRow;
}

// Return row that it reads from 0 to 3, -1 if nothing is inputted
static int readColumn() {
	//unsigned int idrVal = *(portD + 4);
	unsigned int idrVal = portDNew->idr;
	idrVal &= 0x00000F00;
	idrVal >>= 8;
	for (int col = 0; col < 4; col++) {
		// om Col är 3 ska vi läsa bit3, om col är 0 ska vi läsa bit 0.
		if (idrVal & 1) {
			return col;
		}
		idrVal >>= 1;
	}
	return -1;
}

static unsigned char keyValue[4][4] = {{1, 2, 3, 10}, {4, 5, 6, 11}, {7, 8, 9, 12}, {14, 0, 15, 13}};

// Returnera en keycode till knappen som tryckts.
static unsigned char keyb(void) {
	for (int row = 0; row < 4; row++) {
		activateRow(row);
		int column = readColumn();
		if (column != -1) {
			// Row är mellan 0 och 3, column med
			unsigned char val = keyValue[row][column];//, column];
			return val; // Returnera första som den hittar som är klickad på
		}
	}
	return 0xFF; // Returner FF eftersom inget var klickat på
} 

int getKeyDown(unsigned char keyCode)
{
	unsigned char keyDown = keyb();
	if (keyCode == KEYCODE_RIGHT)
	{
		if (keyDown == 6)
		{
			return 1;
		}
	}
	else if (keyCode == KEYCODE_LEFT)
	{
		if (keyDown == 4)
		{
			return 1;
		}
	}
    
    	else if (keyCode == KEYCODE_UP)
	{
		if (keyDown == 2)
		{
			return 1;
		}
	}
    	else if (keyCode == KEYCODE_DOWN)
	{
		if (keyDown == 8)
		{
			return 1;
		}
	}
	
	return 0;
}

#endif //MD407
