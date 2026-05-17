#ifndef _CART_H
#define _CART_H

//include common definitions like structures and macros 
#include "defines.h"

//include search operation function declarations 
#include "search_op_header.h"

//include file operation function declarations 
#include "file_op_header.h"

//include uart communication functions 
#include "uart.h"

//function to update or add products into database 
void update_stock();

//function to add product into cart using product id 
void add_to_cart(char *);

//function to delete product from cart using product id 
void delete_product(char *);

#endif
