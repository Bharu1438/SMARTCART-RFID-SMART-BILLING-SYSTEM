#ifndef _RF_READER_HEADER_H
#define _RF_READER_HEADER_H
/*
Header file for RFID reader module.
This file includes all required headers and declares functions
used for handling RFID-based billing, UART communication,
LCD display, keypad input, buzzer, and interrupts.
*/
#include<lpc21xx.h>

/*
LCD header file.
Provides functions to control LCD display like cmdLCD, stringLCD, numberLCD.
*/
#include"lcd_header.h"

/*
Keypad header file.
Provides keySCAN function to read keypad input.
*/
#include "keypad_header.h"

/*
Delay header file.
Provides delay functions like delay_MS and delay_S.
*/
#include "delay_header.h"

/*
UART0 header file.
Used for communication with external system (like Linux).
*/
#include "uart0_header.h"

/*
UART1 header file.
Used for RFID reader communication.
*/
#include "uart1_header.h"

/*
Buzzer header file.
Used to generate sound indication.
*/
#include "buzzer_header.h"

/*
Interrupt header file.
Used for handling external interrupts and UART interrupts.
*/
#include "interrupt_header.h"

/*
String handling library.
Used for functions like strcpy, strcmp, memset.
*/
#include <string.h>

/*
Standard library.
Used for functions like atoi, sprintf.
*/
#include <stdlib.h>

/*
Function to get numeric input from keypad.
Displays the entered value on LCD dynamically.
*/
int get_amount(int str, int i);

/*
Function to clear buffer and convert integer to string.
*/
void clear_buffer_and_int_convert_to_string(char *buff,int size, int value);

/*
Function to clear buffer and receive string from UART0.
*/
void clear_buffer_and_receive_uart0_string(char *buff, int size);

/*
Main RFID processing function.
Handles entry, delete, and payment operations.
*/
void processRFID(void);

#endif
