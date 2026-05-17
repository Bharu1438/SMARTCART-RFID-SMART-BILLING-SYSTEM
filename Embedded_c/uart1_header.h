#ifndef UART1_HEADER_H
#define UART1_HEADER_H

/*
UART1 uses P0.8 for transmission (TXD1)
and P0.9 for reception (RXD1).
*/


//Defines the crystal oscillator frequency.
#define FOSC 12000000


//Defines CPU clock derived from oscillator.
#define CCLK (FOSC * 5)


//Defines peripheral clock frequency.
#define PCLK (CCLK / 4)


//Defines UART communication baud rate.
#define BAUDRATE 9600


//Calculates divisor value for baud rate generation.
#define DIVISOR (PCLK / (16 * BAUDRATE))


//Defines word length configuration (8-bit mode).
#define WORD_LEN 3

//Defines DLAB bit position in LCR register.
#define DLAB 7

//Defines Data Ready bit position in LSR register.
#define DR 0

//Defines Transmitter Empty bit position in LSR register.
#define TEMT 6

//Function to initialize UART1 module.
void initUart1(void);

#endif

