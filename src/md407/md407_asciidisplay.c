void clearDisplay();
void ascii_gotoxy(int x, int y);
void ascii_write_char(unsigned char c);

void displayAscii(char* str)
{
	clearDisplay();
	ascii_gotoxy(1, 1);

	while (*str)
	{
		ascii_write_char(*str++);
	}
}

// Code below is copy pasted WARNING
// den förväntar sig port E8-15

#include "md407_ports.h"
#include "md407_display_constants.h"

/* addressera ASCII-display och ettställ de bitar som är 1 i x */
void ascii_ctrl_bit_set(unsigned char x) 
{
	
	// Hans
	/*
	 *  unsigned char c;
		c = *GPIO_E_ODRLOW;
		c |= ( B_SELECT | x );
		*GPIO_E_ODRLOW = c;
	 * 
	 * */
	
	
	//*portEOdrLow |= (x | B_SELECT); // B_SELECT gör så att man selectar ASCII-skärmen ist för grafik
	portE->odrLow |= (x | B_SELECT); // B_SELECT gör så att man selectar ASCII-skärmen ist för grafik
	
}

/* addressera ASCII-display och nollställ de bitar som är 1 i x */
void ascii_ctrl_bit_clear(unsigned char x)
{
	//*portEOdrLow &= (B_SELECT | ~x); // B_SELECT gör så att vi inte tar bort dens flagga så vi fortfarande selectar ascii-skärmen
	portE->odrLow  &= (B_SELECT | ~x); // B_SELECT gör så att vi inte tar bort dens flagga så vi fortfarande selectar ascii-skärmen
}


void ascii_write_controller(unsigned char byte) {
	//delay_40ns();	// delay 40 ns
	ascii_ctrl_bit_set(B_E);
	//*portEOdrHigh = byte; // Skriver vår byte till dataregistret
	portE->odrHigh = byte; // Skriver vår byte till dataregistret
	//delay_250ns();	// delay 230 ns ska det vara egentligen
	delay_250ns(); // han vill ha den under nästa rad med det är ologiskt

	ascii_ctrl_bit_clear(B_E);

	//delay_10ns();	// delay 10 ns

}

void ascii_write_cmd (unsigned char command)
{
		ascii_ctrl_bit_clear(B_RS | B_RW); // Sätt rs och rw till 0
		ascii_write_controller(command);
}

void ascii_write_data (unsigned char data)
{
		ascii_ctrl_bit_set(B_RS); // sätt rs till 0
		ascii_ctrl_bit_clear(B_RW); // sätt rw till 0
		ascii_write_controller(data);
}


unsigned char ascii_read_controller()
{
	ascii_ctrl_bit_set(B_E);
	delay_250ns(); // delay 360 ms
	delay_250ns();
	
	//unsigned char readValue = *portEIdrHigh; // VAFAAAN
	unsigned char readValue = portE->idrHigh; // VAFAAAN
	ascii_ctrl_bit_clear(B_E);
	return readValue;
}

unsigned char ascii_read_status()
{
	// sätt porte bit15-bit8 som ingångar
	//*portEModer = 0x00005555;
	portE->moder = 0x00005555;
	ascii_ctrl_bit_clear(B_RS);
	ascii_ctrl_bit_set(B_RW);
	unsigned char readValue = ascii_read_controller();
	//*portEModer = 0x55555555; // Sätter bit15-bit8 som utgångar igen
	portE->moder = 0x55555555; // Sätter bit15-bit8 som utgångar igen
	return readValue;
}

unsigned char ascii_read_data()
{
	// sätt porte bit15-bit8 som ingångar
	//*portEModer = 0x00005555;
	portE->moder = 0x00005555;
	ascii_ctrl_bit_set(B_RS | B_RW);
	unsigned char readValue = ascii_read_controller();
	//*portEModer = 0x55555555; // Sätter bit15-bit8 som utgångar igen
	portE->moder = 0x55555555; // Sätter bit15-bit8 som utgångar igen
	return readValue;
}

void ascii_init() 
{
	// Function set
	while((ascii_read_status() & 0x80)==0x80) {} // Vänta tills display är redo att ta emot kommando
	delay_micro(8); // latenstid för kommando
	// 0x38 = 0011 1000
	ascii_write_cmd(0x38); // 00 111(2rader)0(5x8storlek)00; 00111000 = 0x38 Function Set cmd
	delay_micro(39); // latenstid för kommando
	
	// Display control
	/*while((ascii_read_status() & 0x80)==0x80) {} // Vänta tills display är redo att ta emot kommando
	delay_micro(8); // latenstid för kommando*/
	// 0xE = 0000 1110
	ascii_write_cmd(0xF); // todo ska sätta till 0xE eftersom vi inte vill att markören ska blinka
	delay_micro(39); // latenstid för kommando
	
	// Clear Display
	/*while((ascii_read_status() & 0x80)==0x80) {} // Vänta tills display är redo att ta emot kommando
	delay_micro(8); // latenstid för kommando*/
	ascii_write_cmd(0x1);
	delay_milli(2); // latenstid för kommando
	
	// Entry Mode Set
	/*while((ascii_read_status() & 0x80)==0x80) {} // Vänta tills display är redo att ta emot kommando
	delay_micro(8); // latenstid för kommando*/
	ascii_write_cmd(0x4); // 00000100 = 0x4
	delay_micro(39); // latenstid för kommando
}

// X måste vara mellan 1 och 20 (inc), y måste vara 1 eller 2
void ascii_gotoxy(int x, int y)
{
	while((ascii_read_status() & 0x80)==0x80) {} // Vänta tills display är redo att ta emot kommando
	delay_micro(8); // latenstid för kommando

	int address = x - 1;
	if (y == 2) {
		address += 0x40; // Hoppa 64 tecken som är en rad
	}
	ascii_write_cmd(0x80 | address);
	delay_micro(39); // latenstid för kommando

}

// Ska skriva tecknet c till displayen
void ascii_write_char(unsigned char c)
{
	while((ascii_read_status() & 0x80)==0x80) {} // Vänta tills display är redo att ta emot kommando
	delay_micro(8); // latenstid för kommando

	ascii_write_data(c);
	delay_micro(43); // latenstid för kommando

}

void clearDisplay()
{
	ascii_write_cmd(0x1);
	delay_milli(2); // latenstid för kommando
}

