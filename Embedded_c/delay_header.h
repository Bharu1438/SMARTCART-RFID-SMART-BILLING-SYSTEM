#ifndef _DELAY_HEADER_H
#define _DELAY_HEADER_H
/*
function to generate delay in microseconds
parameter dlyus represents delay time in microseconds
software loop is used to waste cpu cycles and create small delay
*/
void delay_US(unsigned int dlyus);
/*
function to generate delay in milliseconds
parameter dlyms represents delay time in milliseconds
software delay is created by executing a large empty loop
*/
void delay_MS(unsigned int dlyms);
/*
function to generate delay in seconds
parameter dlys represents delay time in seconds
this function produces large delay using software loop
*/
void delay_S(unsigned int dlys);
#endif 

