#ifndef _PAYMENT_H
#define _PAYMENT_H

// include common definitions and structures
#include "defines.h"

// include search related functions
#include "search_op_header.h"

// include file operations
#include "file_op_header.h"

// include uart communication
#include "uart.h"

// declare function for cash transaction
void transaction_cash(float bill);

// declare function for card transaction
void transaction_card(char *card, float amount);

#endif