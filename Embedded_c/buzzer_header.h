/*
Header file for buzzer module.
This file contains macro definitions and function declarations
required to control the buzzer hardware.
*/
#ifndef _BUZZER_HEADER_H
#define _BUZZER_HEADER_H

/*
Including LPC21xx register definitions.
Provides access to GPIO registers like IODIR0, IOSET0, IOCLR0.
*/
#include<lpc21xx.h>

/*
Including delay functions.
Used to generate timing delay for buzzer operation.
*/
#include "delay_header.h"

/*
Macro defining the buzzer pin number.
BUZZER is connected to P0.13.
*/
#define BUZZER 13

/*
Function to initialize buzzer pin as output.
*/
void buzzer_init(void);

/*
Function to turn buzzer ON for a short duration.
*/
void buzzer_on(void);

#endif


