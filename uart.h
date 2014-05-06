#ifndef __UART_H_
#define __UART_H_
#include <avr/io.h>
#include <stdbool.h>
#include "defines.h"

// Berechnungen
#define UBRR_VAL ((F_CPU+BAUD*8)/(BAUD*16)-1)   // clever runden
#define BAUD_REAL (F_CPU/(16*(UBRR_VAL+1)))     // Reale Baudrate
#define BAUD_ERROR ((BAUD_REAL*1000)/BAUD) // Fehler in Promille, 1000 = kein Fehler.
 
#if ((BAUD_ERROR<990) || (BAUD_ERROR>1010))
   #error systemic error of baudrate bigger 1% - thats to damn high! 
#endif

/**
 * \brief Function to initalize the UART
 * \description This function initializes the UART in 8N1 mode with RX and TX
 * enabled. Baudrate can be set via BAUD.
 */
void uart_init(void);

/**
 * \brief Function to put a character to the UART TX line
 * \description This function outputs the given character to the UART and
 * returns true afterwards. This function is blocking and sends the
 * given byte whenever the UART is ready to send!
 * \param in c the character to put to UART
 * \return always true
 */
bool uart_putc(unsigned char c);

/**
 * \brief Function to put a character string (terminated by '\0') to UART TX
 * \description This function outputs the given string to the UART.
 * This Function is blocking and waits for each and every putc operation!
 * \param in s pointer to the first character of the string
 * \return always true
 */
bool uart_puts(char* s);

/**
 * \brief Function to get a character from UART RX in line
 * \description This function gets a single character from UART.
 * This Function is blocking and waits actively for the next byte!
 * \param out out pointer to the location where to store the byte
 * \return always true
 */
bool uart_getc(char* out);

#endif
