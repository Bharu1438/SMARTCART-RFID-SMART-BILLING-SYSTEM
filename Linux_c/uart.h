// prevent multiple inclusion of header file
#ifndef _UART_H
// define macro for header guard
#define _UART_H

// include common definitions and global variables
#include "defines.h"
// include file operations dependency
#include "file_op_header.h"
// include search operations dependency
#include "search_op_header.h"

// declare function to configure uart
int uart_configure(int);
// declare function to read line from uart
int uart_readline(char *, int);
// declare function to send data through uart
void uart_send(const char *);

// end of header guard
#endif