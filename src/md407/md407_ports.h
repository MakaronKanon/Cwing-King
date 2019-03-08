#ifndef MD407_PORTS_H
#define MD407_PORTS_H

/*
 * PortE 0-15 used by Graphic Display and Ascii Display
 * PortD 8-15 used by Keypad
*/

#include "types.h"

// Interface for GPIO port on MD407
typedef struct
{
	uint32 moder;
	uint32 otyper;
	uint32 ospeedr;
	uint32 pupdr;
	union
	{
		uint32 idr;
		struct
		{
			uint8 idrLow;
			uint8 idrHigh;
		};
	};
	union
	{
		uint32 odr;
		struct
		{
			uint8 odrLow;
			uint8 odrHigh;
		};

	};
	uint32 bsrr;
	uint32 lckr;
	uint32 afrl;
	uint32 afrh;
} GPIO, *pGPIO;

// Ports addresses
#define PORTE_BASE 0x40021000
#define GPIO_D_BASE 0x40020C00

// Used to access port E
#define portE ((volatile GPIO*) PORTE_BASE)

// Used to access port D
#define portD ((volatile GPIO*) GPIO_D_BASE)

#endif // MD407_PORTS_H