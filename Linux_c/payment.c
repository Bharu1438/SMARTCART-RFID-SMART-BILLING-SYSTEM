#include "payment.h"

/*
transaction_card handles payment using card
it validates card, checks pin and updates balance
*/
void transaction_card(char *card_buffer, float amount)
{
    // print received card buffer
    printf("%s\n",card_buffer);

    // declare status and pin buffers
    char status[20], pin[10];

    // find account index using card
    int ind = find_account(card_buffer);

    // check if account not found
    if (ind == -1)
    {
        // print invalid card buffer
        printf("%s\n",card_buffer);

#ifdef USE_USB
        // send invalid message to uart
        if(write(uart_fd,"invalid$",8)<0)
        {
            // print error if write fails
            perror("write");
        }
#endif
        // print error message
        printf("Card not found\n");

        // return from function
        return;
    }

    // loop until transaction completes
    while(1)
    {
#ifdef USE_USB
        // prepare pin to send
        sprintf(pin, "%d$", users[ind].pin);

        // send pin to uart
        if(write(uart_fd, pin, strlen(pin))<0)
        {
            // print error if write fails
            perror("write");
        }

        // read status from uart
        uart_readline(status,sizeof(status));
#else
        // print pin locally
        printf("%d\n", users[ind].pin);

        // read status from stdin
        fgets(status, sizeof(status), stdin);

        // remove newline from input
        status[strcspn(status, "\n")] = '\0';
#endif

        // check if pin is correct
        if(strcmp(status, "pin_correct") == 0)
        {
            // deduct amount from balance
            users[ind].balance -= amount;

            // update stock file
            update_stock_file();

            // store bill in file
            add_bill_to_file(amount, card_buffer+1);

            // update bank file
            update_bank_file();

            // clear cart
            cart_size=0;

#ifdef USE_USB
            // send clear signal
            if(write(uart_fd, "clear$", 6)<0)
            {
                // print error if write fails
                perror("write");
            }
#endif
            // print success message
            printf("Paid %.2f via card\n", amount);

            // delay for display
            sleep(1);

            // clear screen
            system("clear");

            // print header
            printf("------Harika Mart------\n");

            // exit loop
            break;
        }

        // check if retry allowed
        else if(strcmp(status,"chance")==0)
        {
            // continue loop
            continue;
        }

        // check if no more chances
        else if(strcmp(status,"nochance")==0)
        {
            // print failure messages
            printf("Try may attempts\n");
            printf("try later\n");

            // clear cart
            cart_size=0;

            // exit loop
            break;
        }
    }
}

/*
transaction_cash handles cash payment
it processes exact, greater or lesser amount cases
*/
void transaction_cash(float bill)
{
    // declare buffers for amount and status
    char amount_buff[20], status_buff[100];

    // declare variables for processing
    int len = 0, amount;

    // declare character variable
    char ch;

#ifdef USE_USB
    // prepare bill amount to send
    sprintf(amount_buff, "%d$", (int)bill);

    // send amount to uart
    if(write(uart_fd, amount_buff, strlen(amount_buff))<0)
    {
        // print error if write fails
        perror("write");
    }

    // loop until transaction completes
    while(1)
    {
        // read status from uart
        uart_readline(status_buff,sizeof(status_buff));
#else
    // print bill amount
    printf("Price : %f\n",bill);

    // read status from stdin
    fgets(status_buff,sizeof(status_buff),stdin);

    // remove newline
    status_buff[strcspn(status_buff,"\n")]='\0';
#endif

        // check success case
        if(status_buff[0]=='s')
        {
            // print success indicator
            printf("S\n");

            // delay
            sleep(1);

            // update stock
            update_stock_file();

            // save bill
            add_bill_to_file(bill, "cash");

            // clear cart
            cart_size=0;

            // clear screen
            system("clear");

            // print header
            printf("------Harika Mart------\n");

            // exit loop
            break;
        }

        // check greater amount case
        else if(status_buff[0]=='g')
        {
            // print indicator
            printf("G\n");

            // delay
            sleep(1);

#ifdef USE_USB
            // read amount from uart
            uart_readline(amount_buff,sizeof(amount_buff));
#else
            // ask user for cash
            printf("Enter cash : ");

            // read input
            fgets(amount_buff,sizeof(amount_buff),stdin);

            // remove newline
            amount_buff[strcspn(amount_buff,"\n")]='\0';
#endif

            // convert string to integer
            amount = atoi(amount_buff);

            // calculate change
            amount-=bill;

            // print return amount
            printf("Return %d amount to customer\n", amount);

            // wait for user confirmation
            printf("Press Enter after returning money\n");
            while((ch = getchar()) != '\n');

            // update stock
            update_stock_file();

            // save bill
            add_bill_to_file(bill, "cash");

            // clear cart
            cart_size=0;

#ifdef USE_USB
            // send clear signal
            if(write(uart_fd, "clear$", 6)<0)
            {
                // print error
                perror("write");
            }
#else
            // clear screen
            system("clear");
#endif
            // exit loop
            break;
        }

        // check less amount case
        else if(status_buff[0]=='l')
        {
            // print indicator
            printf("l\n");

            // delay
            sleep(1);

            // declare card buffer
            char card_buff[50];

            // declare remaining amount
            float amt=0;

#ifdef USE_USB
            // read partial amount
            uart_readline(amount_buff,sizeof(amount_buff));
#else
            // read amount from stdin
            fgets(amount_buff,sizeof(amount_buff),stdin);

            // remove newline
            amount_buff[strcspn(amount_buff,"\n")]='\0';
#endif

            // convert to integer
            amount = atoi(amount_buff);

            // calculate remaining amount
            amt = bill-amount;

            // print remaining
            printf("Remaining amount: %d\n", amount);

#ifdef USE_USB
            // send clear signal
            if(write(uart_fd,"clear$",6)<0)
            {
                // print error
                perror("write");
            }
#else
            // print clear
            printf("clear\n");
#endif

#ifdef USE_USB
            // read card data
            uart_readline(card_buff,sizeof(card_buff));
#else
            // read card from stdin
            fgets(card_buff,sizeof(card_buff),stdin);

            // remove newline
            card_buff[strcspn(card_buff,"\n")]='\0';
#endif

            // save partial bill
            add_bill_to_file(amt,"cash");

            // process card transaction
            transaction_card(card_buff, amount);

            // exit loop
            break;
        }
    }
}