#ifdef MD407

#define SYSTICKADR (0xE000E010)
typedef volatile unsigned int SYSTICKTYPEUINT;
#define PORTSYSTICKUINT (SYSTICKTYPEUINT*)(SYSTICKADR)

#define STK_CTRL ((volatile unsigned int *)(0xE000E010))
#define STK_LOAD ((volatile unsigned int *)(0xE000E014))
#define STK_VAL ((volatile unsigned int *)(0xE000E018))

#include "md407_settings.h"



// todo: räkna ut vad den ska räkna från, vad STK_LOAD ska sättas till
void delay_250ns() 
{
	#ifdef SIMULATOR
	return;
	#endif
	//*PORTSYSTICKUINT &= 0xFFFFFFFE; // Nollställ bit 0
	*STK_CTRL = 0;
	
	//*(PORTSYSTICKUINT + 1) |= 0x0000002A; // Sätt STK_LOAD till högt, men inte mer än 0x00FFFFFF
	*STK_LOAD = 0x29;
	
	//*(PORTSYSTICKUINT + 2) &= 0xFF000000; // Nollställ STK_VAL
	*STK_VAL = 0;
		
	//*PORTSYSTICKUINT |= 0x00000005; // Ettställ bit 0 och 2 i CTRL för att starta
	*STK_CTRL = 5;

	// while (!readBit16clock()) {
	while((*STK_CTRL & 0x10000) == 0) {
		// Be stuck here because bit hasn't gone off
	}
	
	//*PORTSYSTICKUINT &= 0xFFFFFFFE; // Stoppa genom att nollställa bit 0
	*STK_CTRL = 0;
}

void delay_micro(unsigned int micros)
{
	#ifdef SIMULATOR
		micros /= 1000;
		micros++;
	#endif
	
	while (micros > 0) 
	{
		delay_250ns();
		delay_250ns();
		delay_250ns();
		delay_250ns();
		micros--;
	}
}

void delay_milli(unsigned int millis)
{
	delay_micro(millis * 1000);
}

void delay_500ns()
{
	delay_250ns();
	delay_250ns();
}

void delayMilliSecs(unsigned int milliSecs)
{
	delay_milli(milliSecs);
}

#endif