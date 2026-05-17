// Including LPC21xx register definitions (UART, PINSEL, etc.)
#include<lpc21xx.h>

// Including delay functions (used somewhere else in project)
#include "delay_header.h"

// Including UART header macros and declarations
#include "uart0_header.h"

/*
This function initializes UART0 communication.
It configures the required pins for TX and RX,
sets the baud rate using divisor registers,
and enables 8-bit data transmission mode.
*/
void initUart0(void){

	// Clear lower 4 bits of PINSEL0 to reset pin configuration
	PINSEL0 &= ~(15);

	// Configure P0.0 as TX and P0.1 as RX
	PINSEL0 |= 0x05;

	// Enable DLAB and set word length to 8 bits
	U0LCR = (1<<DLAB)|WORD_LEN;

	// Load upper byte of baud rate divisor
	U0DLM = DIVISOR>>8;

	// Load lower byte of baud rate divisor
	U0DLL = DIVISOR;

	// Disable DLAB after setting baud rate
	U0LCR &= ~(1<<DLAB);
}

/*
This function transmits a single character using UART.
It writes the data into the transmit register
and waits until transmission is complete.
*/
void uart0_txchar(unsigned char data){

	// Load data into transmit holding register
	U0THR=data;

	// Wait until transmitter becomes empty
	while(!(U0LSR>>TEMT)&1);
}

/*
This function transmits a string over UART.
Each character is sent one by one until
a null terminator is encountered.
*/
void uart0_txstring(char *str){

	// Loop until end of string
	while(*str){

		// Send current character and move pointer forward
		uart0_txchar(*str++);
	}
}

/*
This function receives a single character from UART.
It waits until data is available in the receive buffer
and then returns the received character.
*/
unsigned char uart0_rxchar(void){

	// Wait until data is available in receive buffer
	while(!((U0LSR>>DR)&1));

	// Read and return received data
	return U0RBR;
}

/*
This function receives a string from UART.
Characters are read continuously until
a terminating symbol '$' is received.
The string is then null terminated.
*/
void uart0_rxstring(char *str)
{
    // Variable to store received character
    char ch;

    // Index to store characters in buffer
    int i = 0;

    // Infinite loop to receive characters
    while(1)
    {
        // Receive one character
        ch = uart0_rxchar();

        // Check for termination character
        if(ch=='$')
        {
            // Add null terminator to string
            str[i] = '\0';

            // Exit loop
            break;
        }

        // Store character in buffer
        str[i++] = ch;
    }
}

/*
This function clears the UART receive buffer.
It continuously reads data until buffer becomes empty.
*/
void uart0_flush()
{
    // Loop while data is available
    while (U0LSR & (1 << 0))
    {
        // Read and discard data
        volatile char dummy = U0RBR;
    }
}

/*
This function checks whether data is available
in the UART receive buffer.
It returns non-zero if data is present.
*/
int uart0_data_available()
{
    // Return status of data ready bit
    return (U0LSR & (1 << 0));
}

/*
This function performs non-blocking string reception.
It reads characters only if available and stores them.
When '$' is received, the string is terminated and returned.
*/
int uart0_rxstring_nonblocking(char *str)
{
    // Static index to maintain position across calls
    static int i = 0;

    // Variable to store received character
    char ch;

    // Check if data is available
    if (uart0_data_available())
    {
        // Read one character
        ch = uart0_rxchar();

        // Check for termination character
        if (ch == '$')
        {
            // Add null terminator
            str[i] = '\0';

            // Reset index for next string
            i = 0; 

            // Indicate complete string received
            return 1; 
        }

        // Store character in buffer
        str[i++] = ch;
    }

    // Indicate string not yet complete
    return 0;
}

