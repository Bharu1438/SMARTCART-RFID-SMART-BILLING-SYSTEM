#ifndef _DEFINES_H
#define _DEFINES_H

// include standard input output functions
#include<stdio.h>

// include standard library functions like malloc, atoi, atof
#include<stdlib.h>

// include string handling functions
#include<string.h>

// include character handling functions
#include<ctype.h>

// include pthread for multithreading support
#include<pthread.h>

// include time related functions
#include<time.h>

// include unix standard functions like sleep
#include<unistd.h>

// define maximum size for arrays
#define MAX 1000

// macro to enable usb uart communication
//#define USE_USB

#ifdef USE_USB

// include unix standard functions
#include<unistd.h>

// include file control options
#include<fcntl.h>

// include terminal control definitions
#include<termios.h>

// define uart device file path
#define LINUX_UART "/dev/ttyUSB0"

// declare uart file descriptor
extern int uart_fd;

// initialize mutex lock for thread synchronization
pthread_mutex_t lock  = PTHREAD_MUTEX_INITIALIZER;

#endif

/*
structure to store product details
contains product name, id, quantity and price
*/
typedef struct{
    // store product name 
    char product_name[20];

    // store product id 
    char product_id[10];

    // store available quantity 
    int quantity;

    // store product price 
    float price;
}product;

/*
structure to store cart details for customer
contains product name, quantity and price
*/
typedef struct{
   // store product name 
    char product_name[20];

   // store quantity in cart 
    int quantity;

   // store product price 
    float price;
}customer;

/*
structure to store user account details
contains bank and card related information
*/
typedef struct{
    // store place information
    char place[50];

    // store ifsc code
    char ifsc[20];

    // store bank name
    char bank[20];

    // store account holder name
    char name[50];

    // store card number
    char cardnumber[20];

    // store pin number
    int pin;

    // store account balance
    float balance;
}account;

// declare product database array
extern product db[MAX];

// declare cart array
extern customer cart[MAX];

// declare users array
extern account users[MAX];

// variable to store number of products
extern int db_size;

// variable to store number of cart items
extern int cart_size;

// variable to store number of users
extern int user_size;

// flag variable for control flow
extern int flag;

#endif
