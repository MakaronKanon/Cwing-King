#ifdef MD407
#include "player.h"

void setPixel(int x, int y, int set)
{
    x -= player.xDelta;
	void setPixelBuffer(unsigned int x, unsigned int y, int set);
	setPixelBuffer(x, y, set);
}

// Renders to screen what is on the buffer
void displayBuffer()
{
	void swapBuffers();
	swapBuffers();
}

void initGraphics()
{
	void graphic_initialize();
	graphic_initialize();
}

void cleanUpGraphics()
{
	// Unused since we never exit game.
}

// Vi behöver ha tillgång till portE
#include "md407_ports.h"
// Vi behöver veta vilka bitar som betyder vad
// Främst för att få vår uint8_t
#include "graphics.h"

#include "md407_display_constants.h"

// För att få tillgång till delay funktionalitet
#include "md407_delay.h"

#include "types.h"

// Här ska vi ha en buffer på hela skärmen 64 * 2 * 64, vi kan spara dom i rätt format direkt
// 128 bredd 8 höjd
uint8 pixelBuffer[128][8];

void setPixelBuffer(unsigned int x, unsigned int y, int set)
{
	x--;
	y--;
	if (x > 127 || y > 63)
	{
		return; // invalid range
	}
	uint8 page = y / 8;
	uint8 bit = y % 8;
	uint8 bitChangeMask = 1 << bit; // bit är 1 blir mask 2, bit är 7 blir mask 0x80

	if (set == 1)
	{
		pixelBuffer[x][page] |= bitChangeMask;
	}
	else
	{
		pixelBuffer[x][page] &= ~bitChangeMask;
	}
}

void clearBuffer()
{
	for (int x = 0; x < 128; x++)
	{
		for (int y = 0; y < 8; y++)
		{
			pixelBuffer[x][y] = 0;
		}
	}
}

// vi ska också ha en swapbuffers/render metod som ritar allt på skärmen.
void swapBuffers()
{
	
	// Render two different times, one for each screen
	for (int screen = 0; screen < 2; screen++)
	{
		for (int x = 0; x < 64; x++)
		{
			for (int y = 0; y < 8; y++)
			{
				uint8 byteToWrite = pixelBuffer[x + screen*64][y];
				//int logicalX = x + 1 + screen * 64;
				//int set = pixelBuffer[logicalX - 1][];
				//pixel(logicalX, y, );
				// address är x
				// page är y
				// chipset är screen-ish
				uint8 address = x;
				uint8 page = y;
				uint8 chipSet;
				
				if (screen == 0)
				{
					chipSet = B_CS1;
				}
				else
				{
					chipSet = B_CS2;
				}
				
				graphic_write_command(CMD_LCD_SET_ADD | address, chipSet); // hur får address plats
				graphic_write_command(CMD_LCD_SET_PAGE | page, chipSet);
				
				graphic_write_data(byteToWrite, chipSet);
				
			}
		}
	}
}



/**
 * @brief Välj grafisk-display och ettställ de bitar som är i x
 * @param x står för flaggbitarna som ska sättas i styrregistret. Bitar som är 0 är opåverkade.
 */
void graphic_ctrl_bit_set(uint8 x)
{
	// Ettställda bitar i x sätts och B_SELECT nollställs för att välja grafisk display 
	//*portEOdrLow = (*portEOdrLow | x) & ~B_SELECT;
	portE->odrLow = (portE->odrLow | x) & ~B_SELECT;
}

/**
 * @brief Välj grafisk-display och nollställ de bitar som är i x
 * @param x står för flaggbitarna som ska nollställas i styrregistret. Andra bitar är opåverkade.
 */
void graphic_ctrl_bit_clear(uint8 x)
{
	// Nollställ ettställda bitar i x och nollställ select
	//*portEOdrLow = (*portEOdrLow & ~x) & ~B_SELECT;
	portE->odrLow = (portE->odrLow & ~x) & ~B_SELECT;
}

/**
 * @brief konfigurerar CS-signalerna
 * @param controller är B_CS1 eller B_CS2 eller båda
 */
void select_controller(uint8 controller)
{
		switch(controller)
		{
			case 0:
				graphic_ctrl_bit_clear(B_CS1 | B_CS2);
				break;
			case B_CS1:
				graphic_ctrl_bit_clear(B_CS2);
				graphic_ctrl_bit_set(B_CS1);
				break;
			case B_CS2:
				graphic_ctrl_bit_clear(B_CS1);
				graphic_ctrl_bit_set(B_CS2);
				break;
			case B_CS1 | B_CS2:
				graphic_ctrl_bit_set(B_CS1 | B_CS2);
				break;
		}
}

/**
 * @brief blocks execution until graphic-display BUSY flag is 0
 */
void graphic_wait_ready()
{
	graphic_ctrl_bit_clear(B_E); // Sätt E = 0
	// sätt bitar 15-8 till ingångnar och 7-0 som utgångar
	// todo gör en funktion av den så vi kan jobba på en mer abstrakt nivå
	//*portEModer = 0x00005555;
	portE->moder = 0x00005555;
	// Sätt RS = 0, RW = 1
	graphic_ctrl_bit_clear(B_RS);
	graphic_ctrl_bit_set(B_RW);
	
	delay_500ns(); // Vänta en halv cykel, tills vi ska sätta på E
	
	uint8 read; // will save read in this byte.
	while (1)
	{
		graphic_ctrl_bit_set(B_E); // Sätt E = 1
		delay_500ns(); // Vänta en halv cykel tills status är färdigläst
		// nu ska vi läsa
		//read = *portEIdrHigh;
		read = portE->idrHigh;
		graphic_ctrl_bit_clear(B_E); // Sätt E = 0
		delay_500ns();
		
		if ((read & LCD_BUSY) == 0) // Om B7 är 0, är den klart och vi ska bryta
		{
			break;
		}
	}
	
	//graphic_ctrl_bit_set(B_E); // Vet inte varför vi slutar genom att sätta E till 1.
	//*portEModer = 0x55555555; // Sätt hela portE som utgång igen. todo: en metod för denna också
	portE->moder = 0x55555555;
}

/**
 * @brief reads a byte from our screen displaymemory, 
 * where to read which page and address should be set before call to this method
 * 
 * @param controller är vilken skärm som ska läsas
 * @return the byte that represent 8 pixels / bits.
 */
uint8 graphic_read(uint8 controller)
{
	graphic_ctrl_bit_clear(B_E); // Sätt E = 0
	// sätt bitar 15-8 till ingångnar och 7-0 som utgångar
	//*portEModer = 0x00005555;
	portE->moder = 0x00005555;
	// Sätt RS = 1, RW = 1
	graphic_ctrl_bit_set(B_RW | B_RS);
	// välj controllern som vi ska läsa från.
	select_controller(controller); 
	
	delay_500ns();
	graphic_ctrl_bit_set(B_E); // E = 1
	delay_500ns(); // Nu kommer den skriva till oss, vi ska alltså läsa nästa
	//uint8_t readValue = *portEIdrHigh; // Läs en byte från porten 
	uint8 readValue = portE->idrHigh;
	graphic_ctrl_bit_clear(B_E);
	
	// sätt alla bitar till ut igen.
	//*portEModer = 0x55555555;
	portE->moder = 0x55555555;
	
	// Här har han en if-sats. Vet inte varför den skulle behövas så jag utelämnar den (sida 107)
	
	if (controller & B_CS1)
	{
		select_controller(B_CS1);
		graphic_wait_ready();
	}
	else if (controller & B_CS2)
	{
		select_controller(B_CS2);
		graphic_wait_ready();
	}
	
	// slut på denna onödiga ifsats ?
	
	return readValue;
}

/**
 * @brief This should be called instead of graphic_read, graphic_read returns nonsense first time
 * so this method calls it twice so we get the data expected.
 * @param controller är vilken skärm som ska läsas
 */
uint8 graphic_read_data(uint8 controller)
{
	graphic_read(controller); // returnerar nonsense
	return graphic_read(controller); // returnerar korrekt data
}

// Writes value display, first it sets controller tho
void graphic_write(uint8 value, uint8 controller)
{
	//*portEOdrHigh = value; // Skriver datan
	portE->odrHigh = value;
	
	select_controller(controller);
	delay_500ns();
	graphic_ctrl_bit_set(B_E);
	delay_500ns();
	graphic_ctrl_bit_clear(B_E);
	
	// Ser till att vi bara selectar en av skärmarna
	if (controller & B_CS1)
	{
		select_controller(B_CS1);
		graphic_wait_ready();
	}
	else if (controller & B_CS2)
	{
		select_controller(B_CS2);
		graphic_wait_ready();
	}
	
	//*portEOdrHigh = 0; // Sätter utPinsens till low igen, jag har gjort det igen
	portE->odrHigh = 0;
	graphic_ctrl_bit_set(B_E);
	select_controller(0); // Unselectar båda skärmarna
}

// Writes command to display
void graphic_write_command(uint8 command, uint8 controller)
{
	graphic_ctrl_bit_clear(B_E);
	select_controller(controller); // väljer CS_1, CS_2 båda eller inga
	graphic_ctrl_bit_clear(B_RS | B_RW);
	graphic_write(command, controller);
}

// Writes data to display
void graphic_write_data(uint8 data, uint8 controller)
{
	graphic_ctrl_bit_clear(B_E);
	select_controller(controller); // väljer CS_1, CS_2 båda eller inga
	graphic_ctrl_bit_clear(B_RW);
	graphic_ctrl_bit_set(B_RS);
	graphic_write(data, controller);
}

// Initerar LCD
void graphic_initialize()
{
	graphic_ctrl_bit_set(B_E);
	delay_micro(10);
	graphic_ctrl_bit_clear(B_CS1 | B_CS2 | B_RST | B_E);
	delay_milli(30);
	graphic_ctrl_bit_set(B_RST);
	delay_milli(100); // stod inte i bok, lade till nu
	graphic_write_command(CMD_LCD_OFF, 			B_CS1 | B_CS2);
	graphic_write_command(CMD_LCD_ON, 			B_CS1 | B_CS2); // toggla display
	graphic_write_command(CMD_LCD_DISP_START, 	B_CS1 | B_CS2); // start = 0
	graphic_write_command(CMD_LCD_SET_ADD, 		B_CS1 | B_CS2); // address = 0
	graphic_write_command(CMD_LCD_SET_PAGE, 	B_CS1 | B_CS2); // page = 0
	select_controller(0); // deaktivera båda CS signalerna
	
}

/**
 * @brief Deaktiverar varenda pixel på skärmen.
 */
void graphic_clear_screen()
{
	for (int page = 0; page < 8; page++)
	{
		graphic_write_command(CMD_LCD_SET_PAGE | page, B_CS1 | B_CS2); // kan köra | page eftersom tre första bitarna håller page address
		graphic_write_command(CMD_LCD_SET_ADD | 0, B_CS1 | B_CS2); // sätt add till 0 eftersom vi vill börja om för varje page.
		for (int address = 0; address < 64; address++)
		{
			graphic_write_data(0, B_CS1 | B_CS2); 
			// När vi skrivit data ökar den address automatisk med 1 så
			// vi måste inte gör det manuellt.
		}
	}
}

#endif // MD407