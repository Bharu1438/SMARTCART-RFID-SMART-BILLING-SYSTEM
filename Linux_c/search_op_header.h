/*
header file to declare search related functions
it prevents multiple inclusion using include guards
*/
#ifndef _SEARCH_OP_HEADER_H
#define _SEARCH_OP_HEADER_H

/*
include common definitions like structures and global variables
*/
#include "defines.h"

/*
function declaration to find product index using product id
*/
int find_product(char *id);

/*
function declaration to find user account index using card id
*/
int find_account(char *id);

/*
function declaration to calculate total bill from cart items
*/
float total_bill();

/*
function declaration to check if given card belongs to manager
*/
char find_manager_card(char *id);

#endif
