/*
header file for LPC214x microcontroller.
provides register definitions for peripherals like UART, GPIO, VIC, etc.
*/
#include <lpc214x.h>

/*
header file for UART0 functions.
contains initialization, transmit, receive functions and related macros.
*/
#include "uart0_header.h"

/*
header file for UART1 functions.
contains initialization and configuration for UART1 communication.
*/
#include "uart1_header.h"

/*
header file for interrupt handling.
contains ISR declarations and interrupt configuration macros.
*/
#include "interrupt_header.h"

/*
header file for LCD interface.
provides functions to initialize LCD, send commands, and display strings.
*/
#include "lcd_header.h"

/*
header file for delay functions.
used to generate time delays required in embedded operations.
*/
#include "delay_header.h"

/*
header file for keypad interface.
provides functions to scan and read keypad inputs.
*/
#include "keypad_header.h"

/*
header file for RFID reader module.
contains functions to read and process RFID data.
*/
#include "rf_reader_header.h"

/*
header file for buzzer control.
provides functions to initialize and control buzzer.
*/
#include "buzzer_header.h"

/*
standard string handling library.
provides functions like strlen, strcmp, strcpy, etc.
*/
#include <string.h>

/*
standard library.
provides utility functions like atoi, malloc, etc.
*/
#include <stdlib.h>

/*
this is the main function of the embedded system.
it initializes all peripherals like UART, LCD, keypad, interrupts, and buzzer.
then it continuously displays a welcome message on LCD
and processes RFID input in an infinite loop.
*/
int main()
{
    // initialize UART0 for communication
    initUart0();

    // initialize UART1 for communication
    initUart1();

    // initialize interrupt system (UART + external interrupts)
    init_interrupt();

    // initialize LCD display
		initLCD();

    // initialize keypad module
		initKPM();

    // initialize buzzer
		buzzer_init();

    // clear LCD display
		cmdLCD(CLEAR_DISPLAY);

    // set cursor to first line
		cmdLCD(GOTO_LINE_ONE);

    // super loop for continuous operation
    while(1)
    {
        // set cursor to first line
				cmdLCD(GOTO_LINE_ONE);

        // display first line message
				stringLCD("Welcome to");

        // move cursor to second line
				cmdLCD(GOTO_LINE_TWO);

        // display second line message
				stringLCD("Hari Mart");

        // process RFID input and related operations
        processRFID();
    }
}

