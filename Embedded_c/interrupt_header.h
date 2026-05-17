#ifndef _INTERRUPT_HEADER_H
#define _INTERRUPT_HEADER_H

//Including LPC21xx register definitions.
#include <lpc21xx.h>

//Defines pin numbers used for external interrupts.
#define EINT0_PIN   16   
#define EINT1_PIN   3   
#define EINT2_PIN   7  

//Defines UART1 interrupt channel number.
#define UART1 7

//Defines PINSEL configurations for external interrupts.
#define EINT0_PINSEL   0x00400001
#define EINT1_PINSEL   0x000000C0
#define EINT2_PINSEL   0x0000C000    

//Defines masks to clear PINSEL bits.
#define EINT0_CLR      (3 << 0)
#define EINT1_CLR      (3 << 6)
#define EINT2_CLR      (3 << 14)

//Defines VIC channel numbers for interrupts.
#define EINT0_CHANNEL  14
#define EINT1_CHANNEL  15
#define EINT2_CHANNEL  16

//Defines interrupt trigger modes.
#define EDGE_TRIGGERED   1
#define LEVEL_TRIGGERED  0

//Defines buffer sizes.
#define MAX 20
#define RX_SIZE 100

//External buffer and flags for UART1.
extern volatile int uart1_ready;
extern char uart1_buffer[MAX];

//External buffer and flags for UART0.
extern char uart0_buffer[RX_SIZE];
extern volatile int uart0_ready;

//Function to initialize interrupts.
void init_interrupt(void);

/*
This ISR handles entry mode trigger using EINT0.
It sets entry_mode flag.
*/
void entry_isr(void) __irq;

/*
This ISR handles delete mode trigger using EINT1.
It sets delete_mode flag.
*/
void delete_isr(void) __irq;

/*
This ISR handles exit mode trigger using EINT2.
It sets exit_mode flag.
*/
void exit_isr(void) __irq;

/*
This ISR handles UART1 receive interrupt.
It reads incoming data and stores it in buffer.
Start and end markers (0x02, 0x03) are used
to detect complete message.
*/
void uart1_isr(void) __irq;

/*
This ISR handles UART0 receive interrupt.
It reads incoming characters and stores them.
String ends when '$' is received.
*/
void UART0_ISR(void) __irq;

#endif

