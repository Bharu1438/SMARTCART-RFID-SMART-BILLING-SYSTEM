/*
include lcd header file
this file contains lcd pin definitions, command macros and lcd function declarations
used for controlling lcd operations like command, data, and display functions
*/
#include "lcd_header.h"

/*
include lpc214x header file
this file contains special function register definitions for lpc2148 microcontroller
used to access gpio registers like iodir0, ioset0, ioclr0 etc
*/
#include <lpc21xx.h>

/*
include delay header file
this file contains delay function declarations used to generate timing delays
delay functions are required to satisfy lcd timing requirements
*/
#include "delay_header.h"


/*
function used to write data or command to lcd
this function sends 8-bit data to lcd data pins
enable signal is toggled to latch the data into lcd
*/
void writeLCD(int ch){

	/*set rw pin to 0 to select write mode of lcd*/
	IOCLR0 = 1<<RW;

	/*clear previous data from lcd data lines*/
	IOCLR0 = 0xff<<LCD;

	/*place new 8-bit data on lcd data pins*/
	IOSET0 = ch<<LCD;

	/*generate enable pulse to latch data into lcd*/
	IOSET0 = 1<<EN;

	/*small delay to satisfy lcd timing*/
	delay_US(1);

	/*bring enable low to complete data write*/
	IOCLR0 = 1<<EN;
	
	/*delay for lcd command execution*/
	delay_MS(2);
}


/*
function to display single character on lcd
rs pin is set high to select data register
character is sent to lcd using writeLCD function
*/
void charLCD(unsigned char ch){

	/*set rs = 1 to select lcd data register*/
	IOSET0 = 1<<RS;

	/*send character to lcd*/
	writeLCD(ch);
}


/*
function used to send command to lcd
rs pin is cleared to select command register
command byte is written to lcd
*/
void cmdLCD(unsigned char ch){

	/*set rs = 0 to select command register*/
	IOCLR0 = 1<<RS;

	/*send command to lcd*/
	writeLCD(ch);
}




/*
function used to initialize lcd module
configures lcd gpio pins and sends initialization commands
initialization sequence follows hd44780 lcd datasheet
*/
void initLCD(void){

	/*configure lcd data pins and control pins as output*/
	IODIR0 |= (255<<LCD) | (1<<RS) | (1<<RW) | (1<<EN);

	/*wait for lcd power stabilization*/
	delay_MS(15);

	/*send function set command multiple times as per datasheet*/
	cmdLCD(BIT8LINE1);
	delay_MS(5);

	cmdLCD(BIT8LINE1);
	delay_US(100);

	cmdLCD(BIT8LINE1);
	
	/*configure lcd for 8-bit mode and 2-line display*/
	cmdLCD(BIT8LINE2);

	/*turn on display and cursor settings*/
	cmdLCD(DISPLAY_ON);

	/*clear lcd display*/
	cmdLCD(CLEAR_DISPLAY);

	/*set cursor movement direction*/
	cmdLCD(CUR_SHIFT);
	
}


/*
function used to display string on lcd
characters are printed sequentially until null character is found
*/
void stringLCD(char *p){

	/*loop runs until null terminator of string*/
	while(*p){

		/*send each character to lcd*/
		charLCD(*p++);
	}
}


/*
function used to display integer number on lcd
number is converted into digits and printed sequentially
*/
void numberLCD(int n){

	/*
	unsigned int range is about 4.3 billion
	which corresponds to maximum 10 digits
	array used to store individual digits
	*/
	int arr[10];

	int cnt = 0;

	/*special case when number is zero*/
	if(n==0){
		charLCD('0');
		return;
	}

	/*extract digits from number*/
	while(n>0){
		arr[cnt++]=n%10;
		n/=10;
	}

	/*display digits in correct order*/
	for(--cnt; cnt>=0; cnt--){
		charLCD(arr[cnt]+'0');
	}
}
