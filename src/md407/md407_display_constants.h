#ifndef MD407_DISPLAY_CONSTANTS_H
#define MD407_DISPLAY_CONSTANTS_H

// These are bit constants used for graphic display

// Bit för Enable i styrregistret
#define B_E 0x40
// Bit för SELECT, ska vara 0-grafikdisplay, 1-asciidisplay
#define B_SELECT 0x4
// Bit för ReadWrite, ska vara 0 då man skriver, och 1 när man läser från enheten
#define B_RW 0x2
// Bit för ?, ska vara 0 om kommando skrivs till eller status läses från displayen. Ska vara 1 om data skrivs eller läses från display
#define B_RS 0x1
// Bit för reset, återställer grafikdisplay till initialtillstånd
#define B_RST 0x20
// Bit för att targeta högra skärmdel 64x64
#define B_CS2 0x10
// Bit för att targeta vänstra skärmdel 64x64: Är båda på skrivs det till båda.
#define B_CS1 0x8

// Cmd för tända display
#define CMD_LCD_ON 0x3F
// Cmd för släcka dispay
#define CMD_LCD_OFF 0x3E
// Cmd för att sätta address
#define CMD_LCD_SET_ADD 0x40
// Cmd för att sätta page
#define CMD_LCD_SET_PAGE 0xB8
// Cmd för att vet ej vad den gör än
#define CMD_LCD_DISP_START 0xC0
// bitmask för BUSY flaggan
#define LCD_BUSY 0x80

#endif //MD407_DISPLAY_CONSTANTS_H