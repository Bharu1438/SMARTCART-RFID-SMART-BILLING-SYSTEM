/*
header file for thread related functionality
it uses include guards to avoid multiple inclusion
*/
#ifndef _THREAD_H
#define _THREAD_H

/*
include common definitions and global variables
*/
#include "defines.h"

/*
include uart communication functions
*/
#include "uart.h"

/*
include search related functions
*/
#include "search_op_header.h"

/*
include cart handling functions
*/
#include "cart.h"

/*
include payment related functions
*/
#include "payment.h"

/*
function declaration for receive thread which handles incoming uart data
*/
void* rx_thread(void *arg);

#endif