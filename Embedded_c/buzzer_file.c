/*
Including buzzer header file.
Provides access to buzzer macros and function declarations.
*/
#include "buzzer_header.h"

/*
This function initializes the buzzer.
It configures the buzzer pin as output so that it can be driven HIGH or LOW.
*/
void buzzer_init(void)
{
    // Set buzzer pin direction as output
	IODIR0 |= (1<<BUZZER);
}

/*
This function turns the buzzer ON for a short duration.
It sets the buzzer pin HIGH, waits for some time,
and then sets it LOW to turn it OFF.
*/
void buzzer_on(void)
{
    // Set buzzer pin HIGH to turn ON
	IOSET0 = (1<<BUZZER);

    // Delay for 50 milliseconds
	delay_MS(50);

    // Clear buzzer pin to turn OFF
	IOCLR0 = (1<<BUZZER);
}

