#ifndef UART0_HEADER_H
#define UART0_HEADER_H
#include "interrupt_header.h"
#include <string.h>
//Macro for selecting TX pin (P0.0)
#define TX 0

//Macro for selecting RX pin (P0.1)
#define RX 0

/*
Macros to configure PINSEL0 for UART function
PINSEL0 bit mapping:
P0.0 -> TxD0 (PINSEL0[1:0] = 01)
P0.1 -> RxD0 (PINSEL0[3:2] = 01)
*/
#define TX_PIN 0x00000001   
#define RX_PIN 0x00000004   

// Crystal Oscillator Frequency (12 MHz)
#define FOSC 12000000

// CPU Clock Frequency (CCLK = 60 MHz)
#define CCLK (FOSC * 5)

// Peripheral Clock Frequency (default = CCLK / 4 = 15 MHz)
#define PCLK (CCLK / 4)

// Baud rate for UART communication
#define BAUDRATE 9600

// Divisor value calculation for baud rate generation
// Formula: PCLK / (16 * BAUDRATE)
#define DIVISOR (PCLK / (16 * BAUDRATE))

/*
LCR (Line Control Register) bits:
Used to configure data format
WORD_LEN (bits 0-1):
00 -> 5-bit
01 -> 6-bit
10 -> 7-bit
11 -> 8-bit (we use this)

DLAB (bit 7):
1 -> Enable access to DLL and DLM registers
0 -> Disable access
*/
#define WORD_LEN 3 
#define DLAB 7

/*
LSR (Line Status Register) bits:
DR (bit 0):
1 -> Data available in receive buffer
0 -> No data available

TEMT (bit 6):
1 -> Transmitter is empty (ready for new data)
0 -> Transmission in progress
*/
#define DR 0
#define TEMT 6

/*
Function to initialize UART communication:
- Configure PINSEL0 for Tx and Rx
- Enable DLAB and set baud rate (DLL, DLM)
- Configure 8-bit data communication
*/
void initUart0(void);

/* 
Function to transmit a single character:
- CPU writes data into Transmit Holding Register (THR)
*/
void uart0_txchar(unsigned char);

/*
Function to transmit a string:
- Sends characters one by one until null character ('\0')
*/
void uart0_txstring(char *);

/*
Function to receive a character:
- CPU reads data from Receive Buffer Register (RBR)
- Returns the received byte
*/
unsigned char uart0_rxchar(void);
void uart0_rxstring(char *);
void uart0_flush(void);
int uart0_data_available(void);
int uart0_rxstring_nonblocking(char *);
#endif
