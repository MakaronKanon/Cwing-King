#ifndef MD407_DELAY_H
#define MD407_DELAY_H

// Specific delay functions needed for MD407 (graphic driver etc.)
void delay_milli(unsigned int millis);
void delay_micro(unsigned int micros);
void delay_250ns(); // Deklaration,prototyp
void delay_500ns();

#endif //MD407_DELAY_H