#include "delay_header.h"
/*
function to generate delay in microseconds
parameter dlyus represents delay time in microseconds
software loop is used to waste cpu cycles and create small delay
*/
void delay_US(unsigned int dlyus){
	/*loop counter variable used for delay calculation*/
	int i;
	/*
	multiply required microseconds by 12 to approximate delay
	each loop iteration consumes several cpu cycles
	this calculation roughly produces 1 microsecond delay
	*/
	for(i = dlyus*12; i>0; i--);
}


/*
function to generate delay in milliseconds
parameter dlyms represents delay time in milliseconds
software delay is created by executing a large empty loop
*/
void delay_MS(unsigned int dlyms){
	/*loop counter variable*/
	int i;
	/*
	1 millisecond = 1000 microseconds
	the loop count is increased to 12000 to approximate 1ms delay
	the processor wastes time executing this empty loop
	*/
	for(i = dlyms*12000; i>0; i--);
}


/*
function to generate delay in seconds
parameter dlys represents delay time in seconds
this function produces large delay using software loop
*/
void delay_S(unsigned int dlys){
	/*loop counter variable*/
	int i;
	/*
	1 second = 1000 milliseconds
	the loop value is multiplied by 12000000 to approximate 1 second
	the cpu repeatedly executes the loop to consume time
	*/
	for(i = dlys*12000000; i>0; i--);
}



