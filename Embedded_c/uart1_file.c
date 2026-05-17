// Including LPC21xx register definitions (UART1, PINSEL, etc.)
#include <lpc21xx.h>

// Including UART1 header macros and declarations
#include "uart1_header.h"

/*
This function initializes UART1 communication.
It configures pins P0.8 and P0.9 for UART1,
sets the baud rate using divisor registers,
enables 8-bit communication mode,
activates FIFO, and enables receive interrupt.
*/
void initUart1(void){

    // Clear PINSEL0 bits corresponding to P0.8 and P0.9
    PINSEL0 &= ~(0xF << 16);

    // Configure P0.8 as TXD1 and P0.9 as RXD1
    PINSEL0 |= (0x5 << 16);

    // Enable DLAB and set word length to 8 bits
    U1LCR = (1 << DLAB) | WORD_LEN;

    // Load upper byte of baud rate divisor
    U1DLM = DIVISOR >> 8;

    // Load lower byte of baud rate divisor
    U1DLL = DIVISOR;

    // Disable DLAB after setting baud rate
    U1LCR &= ~(1 << DLAB);

    // Enable FIFO, reset RX and TX FIFOs
    U1FCR = 0x07;

    // Enable Receive Data Available interrupt
    U1IER = 0x01; 
}

