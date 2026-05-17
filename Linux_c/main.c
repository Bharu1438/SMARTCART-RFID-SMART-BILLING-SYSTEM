#include "defines.h"
// include cart operations 
#include "cart.h"
// include file operations 
#include "file_op_header.h"
// include payment functions 
#include "payment.h"
// include search operations 
#include "search_op_header.h"
// include uart communication 
#include "uart.h"
// include threading functions 
#include "thread.h"

/*
main function is the entry point of program
it initializes data, uart and starts rx thread
*/
int main()
{
    // declare thread variable
    pthread_t t;

    // print startup message
    printf("Hello\n");

    // load stock data from file
    load_stock();

    // load bank data from file
    load_bank();

    // loop through all products and print details
    for(int i = 0; i < db_size; i++){
        // print product details
        printf("%-25s %-15s %-7d %-7.2f\n",db[i].product_name,db[i].product_id,db[i].quantity,db[i].price);
    }

    // loop through all users and print details
    for(int i = 0; i < user_size; i++){
        // print user details
        printf("%-25s %-12s %-15s %-15s %-15s %-5d %-5.2f\n",users[i].place,users[i].ifsc,users[i].bank,users[i].name,users[i].cardnumber,users[i].pin,users[i].balance);
    }

#ifdef USE_USB

    // open uart device
    uart_fd = open(LINUX_UART,O_RDWR);

    // check if uart open failed
    if(uart_fd < 0){
        // print error
        perror("UART");
        // return from program
        return 0;
    }

    // configure uart settings
    uart_configure(uart_fd);

#endif

    // create rx thread
    pthread_create(&t,NULL,rx_thread,NULL);

    // infinite loop to keep program running
    while(1);

    // return from main
    return 0;
}