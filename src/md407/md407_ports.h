/*
 * PortE 0-15 används av graphic display.
 * PortD 8-15 används av keypad
 * PortD 0-7 används av ascii display.
*/

#ifndef MD407_PORTS_H
#define MD407_PORTS_H

// Definerar delar från Port E. Vissa är char's för delar vissa är int's för hela delen.
#define PORTE_BASE 0x40021000/*
#define portEModer (volatile unsigned int*)(PORTE_BASE)
#define portEOtyper (volatile unsigned int*)(PORTE_BASE + 0x4)
#define portEOspeedr (volatile unsigned int*)(PORTE_BASE + 0x8)
#define portEPupdr (volatile unsigned int*)(PORTE_BASE + 0xC)*/
/*
#define portEIdrLow (volatile unsigned char*)(PORTE_BASE + 0x10)
#define portEIdrHigh (volatile unsigned char*)(PORTE_BASE + 0x11)
#define portEOdrLow (volatile unsigned char*)(PORTE_BASE + 0x14)
#define portEOdrHigh (volatile unsigned char*)(PORTE_BASE + 0x15)
*/
#define GPIO_D_BASE (0x40020C00)/*
typedef volatile unsigned int portType;
#define portD ((portType*) GPIO_D_BASE)*/

typedef unsigned int uint32;
typedef unsigned short uint16;
typedef unsigned char uint8;

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



#define portE ((volatile GPIO*) PORTE_BASE)
#define portDNew ((volatile GPIO*) GPIO_D_BASE)

#endif // MD407_PORTS_H