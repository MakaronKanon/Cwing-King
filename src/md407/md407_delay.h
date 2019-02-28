#ifndef MD407_DELAY_H
#define MD407_DELAY_H

/**
 * @brief blocks execution for some milliseconds.
 * @param milliSecs, how long to delay.
 */
void delayMilliSecs(unsigned int milliSecs);

void delay_milli(unsigned int millis);
void delay_micro(unsigned int micros);
void delay_250ns(); // Deklaration,prototyp
void delay_500ns();

#endif //MD407_DELAY_H