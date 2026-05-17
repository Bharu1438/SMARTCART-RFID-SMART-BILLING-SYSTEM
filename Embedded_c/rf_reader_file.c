/*
Including RFID reader header file.
Provides all required declarations and macros.
*/
#include "rf_reader_header.h"

/*
Including standard I/O library.
Used for functions like sprintf.
*/
#include <stdio.h>

/*
Global flags for different modes of operation.
*/
int entry_mode = 0;
int delete_mode = 0;
int exit_mode = 0;

/*
This function reads multiple digits from keypad.
It allows user to enter numbers, delete last digit,
and displays the entered value on LCD.
*/
int get_amount(int str, int i) {
    
    // Variable to store final value
    int value = 0, num;

    // Infinite loop to read keypad input
    while (1) {

        // Read key from keypad
        num = keySCAN();

        // If ENTER key is pressed, break loop
        if (num == 11)
            break;

        // If BACKSPACE key is pressed
        else if (num == 10)
            value = value / 10;

        // If numeric key is pressed
        else if (num >= 0 && num <= 9)
            value = (value * 10) + num;

        // Set LCD cursor position
        cmdLCD(str + i);

        // Clear display area
        stringLCD("         ");

        // Reset cursor position
        cmdLCD(str + i);

        // Display value if not zero
        if (value != 0)
            numberLCD(value);
    }

    // Return final entered value
    return value;
}

/*
This function clears buffer and converts integer to string.
*/
void clear_buffer_and_int_convert_to_string(char* buff, int size, int value) {
    
    // Clear buffer memory
    memset(buff, 0, size);

    // Convert integer value to string
    sprintf(buff, "%d", value);
}

/*
This function clears buffer and receives string from UART0.
*/
void clear_buffer_and_receive_uart0_string(char* buff, int size) {
    
    // Flush UART0 buffer
	uart0_flush();

    // Clear buffer memory
    memset(buff, 0, size);

    // Receive string from UART0
    uart0_rxstring(buff);
}

/*
This function receives data from UART0 using interrupt flag.
*/
void uart0_recv_intr(char *buff)
{
    // Reset ready flag
	uart0_ready=0;

    // Wait until data is ready
	while(!uart0_ready);

    // Reset flag again
	uart0_ready=0;

    // Copy received data to buffer
	strcpy(buff,uart0_buffer);
}

/*
This function displays thank you message on LCD.
*/
void display_thank(void) {
    
    // Clear LCD display
    cmdLCD(CLEAR_DISPLAY);

    // Move cursor to first line
    cmdLCD(GOTO_LINE_ONE);

    // Display message
    stringLCD("Thank you");

    // Move to second line
    cmdLCD(GOTO_LINE_TWO);

    // Display message
    stringLCD("Visit Again");

    // Delay for 3 seconds
    delay_MS(3000);

    // Clear display again
    cmdLCD(CLEAR_DISPLAY);
}

/*
Main function to process RFID operations.
Handles entry mode, delete mode, and payment mode.
*/
void processRFID(void) {
    
    // Variable declarations
    int pin, atmpin, pin_count;
    float value = 0, value2 = 2, remaining = 0;
    int choice;
    char buff[12], product_price[12];

    // Static variables for role and count
    static int role = 0, count = 0;

    // ENTRY MODE
    if (entry_mode == 1) {

        // Clear LCD
		cmdLCD(CLEAR_DISPLAY);

        // Display message
        cmdLCD(GOTO_LINE_ONE);
        stringLCD("Scan Your Card");

        // Reset role
        role = 0;

        // Clear UART1 buffer
        uart1_buffer[0] = '\0';

        // Reset ready flag
        uart1_ready = 0;

        // Infinite loop
        while (1) {

            // Break if mode changes
			if (delete_mode == 1 || exit_mode == 1)
			{
                entry_mode=0;
				break;
			}

            // If RFID data is ready
            if (uart1_ready) {

                // Copy RFID data
                strcpy(buff, uart1_buffer);

                // Reset flag
                uart1_ready = 0;

                // Send data to UART0
                uart0_txstring(buff);
                uart0_txchar('$');

                // Receive response
				uart0_ready=0;
				uart0_recv_intr(buff);

                // Manager mode
				if (strcmp(buff, "M") == 0) {

                    // Display updating message
					cmdLCD(CLEAR_DISPLAY);
					cmdLCD(GOTO_LINE_ONE);
					stringLCD("Manager Updating");
					cmdLCD(GOTO_LINE_TWO);
					stringLCD("Products......");

                    // Receive status
					uart0_recv_intr(buff);

                    // If update completed
					if (strcmp(buff, "completed") == 0) {

                        // Reset entry mode
						entry_mode = 0;

                        // Display success message
						cmdLCD(CLEAR_DISPLAY);
						cmdLCD(GOTO_LINE_ONE);
						stringLCD("products Updated");
						cmdLCD(GOTO_LINE_TWO);
						stringLCD("Successfully");

                        // Delay
						delay_S(2);

                        // Clear display
						cmdLCD(CLEAR_DISPLAY);

                        // Exit loop
						break;
					}
				}		

                // Customer mode
				else if(strcmp(buff,"C")==0)
				{
                    // Receive product price
					uart0_recv_intr(product_price);

                    // Receive total price
					uart0_recv_intr(buff);

                    // Display on LCD
					cmdLCD(CLEAR_DISPLAY);
					cmdLCD(GOTO_LINE_ONE);
					stringLCD("Price : ");
					stringLCD(product_price);
					cmdLCD(GOTO_LINE_TWO);
					stringLCD("Total : ");
					stringLCD(buff);
				}
			}
        }

        // Reset entry mode
        entry_mode = 0;
    }

    // DELETE MODE
    if (delete_mode == 1) {

        // Display delete mode
        cmdLCD(CLEAR_DISPLAY);
        cmdLCD(GOTO_LINE_ONE);
        stringLCD("DELETE MODE");
        cmdLCD(GOTO_LINE_TWO);
        stringLCD("Scan Card");

        // Reset buffer and flag
        uart1_buffer[0] = '\0';
        uart1_ready = 0;

        // Loop until mode ends
        while (delete_mode == 1) {

            // Decrease count
            count--;

            // Break if other mode triggered
            if (entry_mode || exit_mode)
                break;

            // If RFID data ready
            if (uart1_ready) {

                // Reset flag
                uart1_ready = 0;

                // Buzzer indication
                buzzer_on();

                // Send delete command
                uart0_txchar('D');
                uart0_txstring(uart1_buffer);
                uart0_txchar('$');

                // Receive data
				uart0_recv_intr(product_price);
				uart0_recv_intr(buff);

                // Display result
				cmdLCD(CLEAR_DISPLAY);

                // If valid price
				if(product_price[0]>='0' && product_price[0]<='9')
				{
					cmdLCD(GOTO_LINE_ONE);
					stringLCD("Price : -");
					stringLCD(product_price);
					cmdLCD(GOTO_LINE_TWO);
					stringLCD("Total : ");
					stringLCD(buff);
				}
                else
				{
					cmdLCD(GOTO_LINE_ONE);
					stringLCD(product_price);
					cmdLCD(GOTO_LINE_TWO);
					stringLCD("Total : ");
					stringLCD(buff);
				}
            }
        }

        // Reset delete mode
        delete_mode = 0;
    }

    // EXIT MODE (PAYMENT)
    if (exit_mode == 1) {

        // If cart empty
        if (count == 0) {

            // Display message
            cmdLCD(CLEAR_DISPLAY);
            cmdLCD(GOTO_LINE_ONE);
            stringLCD("Cart Empty");

            // Delay
            delay_MS(2000);

            // Reset mode
            exit_mode = 0;
            return;
        }

        // Payment selection label
		label:

        // Display options
        cmdLCD(CLEAR_DISPLAY);
        cmdLCD(GOTO_LINE_ONE);
        stringLCD("Payment Method");
        cmdLCD(GOTO_LINE_TWO);
        stringLCD("1.CASH  2.CARD");

        // Read choice
        choice = keySCAN();

        // CASH PAYMENT
        if (choice == 1) {

            // Send cash request
            uart0_txstring("Cash$");

            // Delay
			delay_S(1000);

            // Receive amount
            clear_buffer_and_receive_uart0_string(buff, sizeof(buff));

            // Convert to integer
            value = atoi(buff);

            // Ask user to enter amount
            cmdLCD(CLEAR_DISPLAY);
            cmdLCD(GOTO_LINE_ONE);
            stringLCD("Enter Amount");

            // Read user amount
            value2 = get_amount(GOTO_LINE_TWO, 0);

            // Exact match
            if (value == value2) {

                uart0_txstring("success$");
                display_thank();
            }

            // More amount entered
            else if (value < value2) {

                uart0_txstring("greater$");

                value2 = value2 - value;

                clear_buffer_and_int_convert_to_string(buff, sizeof(buff), value2);

                uart0_txstring(buff);

				delay_S(1000);

                clear_buffer_and_receive_uart0_string(buff, sizeof(buff));

                if (strncmp(buff, "clear",5) == 0) {
                    display_thank();
                }
            }

            // Less amount entered
            else if (value > value2) {

                remaining = value - value2;

                uart0_txstring("lessamount");
				uart0_txchar('$');

                clear_buffer_and_int_convert_to_string(buff, sizeof(buff), remaining);

				uart0_txstring(buff);

				delay_S(1000);

				clear_buffer_and_receive_uart0_string(buff, sizeof(buff));

                if (strcmp(buff, "clear") == 0) {
                    choice = 2;
                }
            }
        }

        // CARD PAYMENT
        if (choice == 2) {

            // Ask to swipe card
            cmdLCD(CLEAR_DISPLAY);
            cmdLCD(GOTO_LINE_ONE);
            stringLCD("Swipe Your Card ");

            // Reset flag
			uart1_ready = 0;

            // Wait for card
            while (!uart1_ready);

            // Buzzer indication
            buzzer_on();

            // Copy card data
            strcpy(buff, uart1_buffer);

            // Reset flag
			uart1_ready = 0;

            // Send card data
            uart0_txchar('B');
            uart0_txstring(buff);
            uart0_txchar('$');

			delay_MS(300);

            // Receive response
			uart0_recv_intr(buff);

            // If invalid card
			if(strcmp(buff,"invalid")==0)
			{
				goto label;
			}
			else
			{
                // Get ATM pin
				delay_S(1000);
                atmpin = atoi(buff);

                // PIN verification loop
                while (1) {

                    cmdLCD(CLEAR_DISPLAY);
                    cmdLCD(GOTO_LINE_ONE);
                    stringLCD("ENTER PIN:");
                    cmdLCD(GOTO_LINE_TWO);
                    stringLCD("Press ENTER");

                    pin = get_amount(GOTO_LINE_ONE, 10);

                    pin_count++;

                    // Correct pin
                    if (pin == atmpin) {

                        uart0_txstring("pin_correct$");

						uart0_recv_intr(buff);

						cmdLCD(CLEAR_DISPLAY);
						cmdLCD(GOTO_LINE_ONE);
						stringLCD("Payment Success");
						cmdLCD(GOTO_LINE_TWO);
						stringLCD(buff);

						delay_MS(2500);

                        display_thank();
                        break;
                    }

                    // Retry attempts
                    else if (pin != atmpin && pin_count <= 2) {

                        uart0_txstring("chance$");

                        cmdLCD(CLEAR_DISPLAY);
                        cmdLCD(GOTO_LINE_ONE);
                        stringLCD("Wrong Pin");
                        cmdLCD(GOTO_LINE_TWO);
                        stringLCD("Try Again");

                        delay_MS(2000);
                    }

                    // Max attempts reached
                    else if (pin != atmpin && pin_count == 3) {

                        uart0_txstring("nochance$");

                        cmdLCD(CLEAR_DISPLAY);
                        cmdLCD(GOTO_LINE_ONE);
                        stringLCD("So many attempts");
                        cmdLCD(GOTO_LINE_TWO);
                        stringLCD("Try Later");

                        delay_MS(2000);
						break;
                    }
                }
            }
        }

        // Clear display and reset exit mode
        cmdLCD(CLEAR_DISPLAY);
        exit_mode = 0;
    }
}
