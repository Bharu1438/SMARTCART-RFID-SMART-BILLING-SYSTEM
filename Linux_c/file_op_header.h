#ifndef _FILE_OP_HEADER_H
#define _FILE_OP_HEADER_H

// include common definitions and global variables
#include "defines.h"

// function to load stock data from file into database
void load_stock();

// function to load bank data from file into users database
void load_bank();

// function to update stock file with current database values
void update_stock_file();

// function to update bank file with current users data
void update_bank_file();

// function to append bill details into file
void add_bill_to_file(float cash, char *mode);

#endif
