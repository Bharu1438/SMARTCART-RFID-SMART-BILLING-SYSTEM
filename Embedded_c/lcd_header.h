#ifndef _LCD_HEADER_H
#define _LCD_HEADER_H

//starting gpio pin position where lcd data lines are connected
#define LCD 17

//rs pin used to select lcd register (command or data)
#define RS 25

//rw pin used to select read or write operation
#define RW 27

//enable pin used to latch data into lcd
#define EN 14

//macro used to clear entire lcd display
#define CLEAR_DISPLAY 0x01

//macro used to return cursor to starting position
#define CURSOR_START 0x02

//macro used to turn off lcd display
#define DISPLAY_OFF 0x08

//macro used to turn on lcd display
#define DISPLAY_ON 0x0C

//macro used to turn on display with visible cursor
#define DISPLAY_CURSOR 0x0E

//macro used to turn on display with blinking cursor block
#define DISPLAY_BLOCK 0x0F

//command used to configure lcd in 8-bit mode single line
#define BIT8LINE1 0x30

//command used to configure lcd in 8-bit mode two lines
#define BIT8LINE2 0x38

//command used to configure lcd in 4-bit mode single line
#define BIT4LINE1 0x20

//command used to configure lcd in 4-bit mode two lines
#define BIT4LINE2 0x28

//command used to move cursor to first line starting position
#define GOTO_LINE_ONE 0x80

//command used to move cursor to second line starting position
#define GOTO_LINE_TWO 0xC0

//command used to move cursor to third line starting position
#define GOTO_LINE_THREE 0x90

//command used to move cursor to fourth line starting position
#define GOTO_LINE_FOUR 0xD0

//command used to set entry mode and shift cursor right after character display
#define CUR_SHIFT 0x06

//command used to shift lcd display towards left
#define SHIFT_DISP_LEFT 0x10

//command used to shift lcd display towards right
#define SHIFT_DISP_RIGHT 0x14

//function prototype used to write command or data to lcd
void writeLCD(int);

//function prototype used to display single character on lcd
void charLCD(unsigned char);

//function prototype used to send command to lcd
void cmdLCD(unsigned char);

//function prototype used to initialize lcd module
void initLCD(void);

//function prototype used to display string on lcd
void stringLCD(char *);

//function prototype used to display integer number on lcd
void numberLCD(int);

#endif
