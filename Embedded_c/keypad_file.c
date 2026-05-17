/*
include lpc214x header file
this file contains special function register definitions for lpc2148 microcontroller
used to access gpio registers like iodir0, ioset0, ioclr0 etc
*/
#include<lpc21xx.h>


/*
include delay header file
this file contains delay function declarations used to generate timing delays
delay functions are required to satisfy lcd timing requirements
*/
#include "delay_header.h"

//include keypad function prototypes and macros
#include "keypad_header.h"

/*2D array used to map row and column position to keypad value
each element corresponds to key value of 4x4 keypad
*/
int arr[4][4]={
{7,8,9,12},
{4,5,6,13},
{1,2,3,14},
{10,0,11,15}
};

//function used to initialize keypad module
void initKPM(void){
//configure row pins as output so microcontroller can drive them
WNIBBLE(IODIR1,ROW,15);
}

//function used to detect if any column key is pressed
int colSCAN(void){
//read column pins and check if any pin becomes low
if(RNIBBLE(IOPIN1,COL) < 15){
//column value less than 1111 indicates key press
return 0;
}
else{
//all column pins high indicates no key press
return 1;
}
}

//function used to determine which row the pressed key belongs to
int rowCHECK(void){
//variable used to store row number
int rno;
/*
activate one row at a time by making it low
if column detects low signal then key belongs to that row
*/
for(rno = 0; rno < 4; rno++){
//drive one row low while keeping others high
WNIBBLE(IOPIN1,ROW,~(1<<rno));
//check if key press detected in column
if(colSCAN()==0){
//stop scanning rows when key detected
break;
}
}
//reset all row pins to low
WNIBBLE(IOPIN1,ROW,0x0);
//return detected row number
return rno;
}

//function used to determine which column key is pressed
int colCHECK(void){
//variable used to store column number
int cno;
//scan each column pin
for(cno = 0; cno<4; cno++){
//check column pin status
if(((IOPIN1>>(COL+cno))&1)==0){
//stop when low detected indicating pressed key
break;
}
}
//return detected column number
return cno;
}

//function used to perform complete keypad scan
int keySCAN(void){
//variables used for row number, column number and key value
int r,c,keyval;
//wait until key press occurs
while(colSCAN());
//determine row number of pressed key
r = rowCHECK();
//determine column number of pressed key
c = colCHECK();
//retrieve key value using row and column index
keyval = arr[r][c];
//wait until key is released
while(!colSCAN());
//delay used for key debouncing to avoid multiple detections
delay_MS(500);
//return detected key value
return keyval;
}



//function used to perform complete keypad scan
int keyySCAN(void){
//variables used for row number, column number and key value
int r,c,keyval;
//wait until key press occurs
while(colSCAN());
//determine row number of pressed key
r = rowCHECK();
//determine column number of pressed key
c = colCHECK();
//retrieve key value using row and column index
keyval = arr[r][c];
//delay used for key debouncing to avoid multiple detections
//return detected key value
return keyval;
}

/*
function used to check key press for timeout condition
returns 1 when key press detected
returns 0 when no key press detected
*/
int is_keyPressed()
{
//check if any column pin becomes low indicating key press
if((IOPIN1 & 0x00F00000) != 0x00F00000)
return 1;
//return 0 if no key press detected
return 0;
}

/*
This function reads multiple digit input from keypad.
It continuously scans keys and constructs a number.
Digits (0–9) are appended to form the number.
Special keys:
- 10 ? acts as backspace (removes last digit)
- 11 ? acts as enter (ends input)
Finally, it returns the constructed integer value.
*/
int multiple_digit(void)
{
    // Variable to store the final number
    int value = 0;

    // Variable to store each key press
    int num;

    // Infinite loop to keep reading input
    while(1)
    {
        // Read key value from keypad
        num = keySCAN();

        // If enter key (11) is pressed, exit loop
        if(num == 11)
            break;

        // If backspace key (10) is pressed
        else if(num == 10)
        {
            // Remove last digit
            value = value / 10;
        }

        // If digit key (0–9) is pressed
        else if(num >= 0 && num <= 9)
        {
            // Append digit to the number
            value = (value * 10) + num;
        }
    }

    // Return the final constructed value
    return value;
}

