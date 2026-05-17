#include "interrupt_header.h"
#include "uart0_header.h"

/*
Defines maximum buffer size for UART1 reception.
*/
#define MAX 20

/*
Buffer to store UART1 received data.
*/
char uart1_buffer[MAX];

/*
Index to track current position in UART1 buffer.
*/
volatile int uart1_index = 0;

/*
Flag to indicate UART1 message is ready.
*/
volatile int uart1_ready = 0;

/*
Temporary variables used in ISR.
*/
char i, ch, dummy;

/*
Flag used for card-related logic.
*/
int card_flag;

/*
Defines maximum buffer size for UART0 reception.
*/
#define RX_SIZE 100

/*
Buffer to store UART0 received data.
*/
char uart0_buffer[RX_SIZE];

/*
Index to track current position in UART0 buffer.
*/
volatile int uart0_index = 0;

/*
Flag to indicate UART0 message is ready.
*/
volatile int uart0_ready = 0;

/*
External mode control flags.
*/
extern int entry_mode;
extern int delete_mode;
extern int exit_mode;

/*
This function initializes external interrupts and UART interrupts.
It configures pin functions, enables interrupt channels,
assigns ISR handlers, and sets interrupt modes.
*/
void init_interrupt(void)
{
    // Clear PINSEL bits for EINT1 and EINT2
    PINSEL0 &= ~(EINT1_CLR | EINT2_CLR);

    // Clear PINSEL bits for EINT0
    PINSEL1 &= ~(EINT0_CLR);

    // Configure pins for external interrupts
    PINSEL0 |= (EINT1_PINSEL | EINT2_PINSEL);

    // Configure pin for EINT0
    PINSEL1 |= (EINT0_PINSEL);

    // Enable UART1, UART0, and external interrupts in VIC
    VICIntEnable |= (1<<6) | (1<<UART1) | (1<<EINT0_CHANNEL) | (1<<EINT1_CHANNEL) | (1<<EINT2_CHANNEL);

    // Assign UART1 ISR to vector slot 0
    VICVectCntl0 = (1<<5)|UART1;

    // Set UART1 ISR address
    VICVectAddr0 = (unsigned int) uart1_isr;

    // Assign EINT0 ISR to vector slot 1
    VICVectCntl1 = (1<<5) | EINT0_CHANNEL;

    // Set EINT0 ISR address
    VICVectAddr1 = (unsigned int)entry_isr;

    // Assign EINT1 ISR to vector slot 2
    VICVectCntl2 = (1<<5) | EINT1_CHANNEL;

    // Set EINT1 ISR address
    VICVectAddr2 = (unsigned int)delete_isr;

    // Assign EINT2 ISR to vector slot 3
    VICVectCntl3 = (1<<5) | EINT2_CHANNEL;

    // Set EINT2 ISR address
    VICVectAddr3 = (unsigned int)exit_isr;

    // Assign UART0 ISR to vector slot 4
    VICVectCntl4 = (1 << 5) | 6;

    // Set UART0 ISR address
    VICVectAddr4 = (unsigned int)UART0_ISR;

    // Configure external interrupts as edge triggered
    EXTMODE = (1<<0) | (1<<1) | (1<<2); 

    // Enable UART0 receive interrupt
    U0IER = 0x01;
}

/*
This ISR handles UART1 receive interrupt.
It reads incoming data and stores it in buffer.
Start and end markers (0x02, 0x03) are used
to detect complete message.
*/
void uart1_isr(void) __irq
{
    // Check if interrupt is due to received data
    if (U1IIR & 0x04)
    {
        // Read received character
        ch = U1RBR;

        // Check for start marker
        if (ch == 0x02)
        {
            // Reset buffer index
            uart1_index = 0;
        }

        // Check for end marker
        else if (ch == 0x03)
        {
            // Null terminate string
            uart1_buffer[uart1_index] = '\0';

            // Set ready flag
            uart1_ready = 1;
        }

        // Store normal character
        else
        {
            // Add character to buffer
            uart1_buffer[uart1_index++] = ch;
        }
    }

    // Handle other interrupt sources
    else
    {
        // Read IIR to clear interrupt
        dummy = U1IIR;
    }

    // Acknowledge interrupt completion
    VICVectAddr = 0;
}

/*
This ISR handles UART0 receive interrupt.
It reads incoming characters and stores them.
String ends when '$' is received.
*/
void UART0_ISR(void) __irq
{
    // Variable to store interrupt source
    unsigned int intsrc;

    // Variable to store received character
    char ch;

    // Read interrupt source
    intsrc = U0IIR & 0x0E;

    // Check if interrupt is receive related
    if (intsrc == 0x04 || intsrc == 0x0C)
    {
        // Read received character
        ch = U0RBR;

        // If not end marker
        if (ch != '$')
        {
            // Check buffer boundary
            if (uart0_index < RX_SIZE - 1)

                // Store character
                uart0_buffer[uart0_index++] = ch;
        }

        // If end marker received
        else
        {
            // Null terminate string
            uart0_buffer[uart0_index] = '\0';

            // Reset index
            uart0_index = 0;

            // Set ready flag
            uart0_ready = 1;
        }
    }

    // Acknowledge interrupt completion
    VICVectAddr = 0;
}

/*
This ISR handles entry mode trigger using EINT0.
It sets entry_mode flag.
*/
void entry_isr(void) __irq
{
    // Set entry mode flag
    entry_mode = 1;

    // Clear interrupt flag
    EXTINT = 1<<0;   

    // Acknowledge interrupt
    VICVectAddr = 0;
}

/*
This ISR handles delete mode trigger using EINT1.
It sets delete_mode flag.
*/
void delete_isr(void) __irq
{
    // Set delete mode flag
    delete_mode = 1;

    // Clear interrupt flag
    EXTINT = 1<<1;

    // Acknowledge interrupt
    VICVectAddr = 0;
}

/*
This ISR handles exit mode trigger using EINT2.
It sets exit_mode flag.
*/
void exit_isr(void) __irq
{
    // Set exit mode flag
    exit_mode = 1;

    // Clear interrupt flag
    EXTINT = 1<<2;

    // Acknowledge interrupt
    VICVectAddr = 0;
}

