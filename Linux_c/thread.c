/*
include thread header file for function declarations and dependencies
*/
#include "thread.h"

/*
this function runs as a separate thread
it continuously reads data from uart and performs actions based on input
*/
void* rx_thread(void *arg)
{
    // declare buffer to store incoming uart data and role variable
    char buff[100], role;

    // declare variable to store total bill
    float bill;

    // infinite loop to continuously read uart data
    while (1)
    {
        // read data from uart into buffer
        if (uart_readline(buff, sizeof(buff)) > 0)
        {
            // print received data
            printf("%s\n", buff);

            // add delay to avoid fast execution
            sleep(1);

            // check if data is not special command and determine role
            if (buff[0] != 'B' && buff[0] != 'D' && buff[0] != 'P')

            // find whether card belongs to manager
            role = find_manager_card(buff);

            // assign default role as user
            else
            role = 'U';

            // check if command is pay
            if (strcmp(buff, "Pay") == 0)
            {
                // reset flag
                flag = 0;

                // calculate total bill
                bill = total_bill();

                // perform cash transaction
                transaction_cash(bill);
            }

            // check for payment response messages
            else if (strcmp(buff, "success") == 0 ||
                     strcmp(buff, "greater") == 0 ||
                     strcmp(buff, "less_amount") == 0)
            {
                // clear cart after transaction
                cart_size = 0;

                // clear terminal screen
                printf("\033[2J\033[H");
            }

            // check if delete command is received
            else if (buff[0] == 'D')
            {
                // delete product from cart
                delete_product(buff + 1);
            }

            // check if card payment is requested
            else if (buff[0] == 'B')
            {
                // print card mode
                printf("Card\n");

                // reset flag
                flag = 0;

                // calculate total bill
                bill = total_bill();

                // perform card transaction
                transaction_card(buff, bill);
            }

            // handle rfid card inputs
            else
            {
                // check if role is manager
                if (role == 'M')
                {
                    // check if system is in customer mode
                    if (flag == 2)
                    {
                        // print error message
                        printf("Master card not accepted during Customer mode\n");

#ifdef USE_USB
                        // send customer mode response via uart
                        write(uart_fd, "C$", 2);
#else
                        // print customer mode response
                        printf("C\n");
#endif
                        // skip current iteration
                        continue;
                    }

                    // set flag to manager mode
                    flag = 1;

#ifdef USE_USB
                    // send manager mode response via uart
                    write(uart_fd, "M$", 2);
#else
                    // print manager mode response
                    printf("M\n");
#endif

                    // update stock using manager card
                    update_stock(buff);
                }

                // check if role is customer
                else if (role == 'C')
                {
                    // check if system is in manager mode
                    if (flag == 1)
                    {
                        // print error message
                        printf("Customer card not accepted during update\n");

#ifdef USE_USB
                        // send manager mode response via uart
                        write(uart_fd, "M$", 2);
#else
                        // print manager mode response
                        printf("M\n");
#endif
                        // skip current iteration
                        continue;
                    }

                    // set flag to customer mode
                    flag = 2;

#ifdef USE_USB
                    // send customer mode response via uart
                    write(uart_fd, "C$", 2);
#else
                    // print customer mode response
                    printf("C\n");
#endif

                    // add product to cart using customer card
                    add_to_cart(buff);
                }
            }
        }
    }
}