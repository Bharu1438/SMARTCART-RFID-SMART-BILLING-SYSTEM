#include "defines.h"

/*
this file defines all global variables declared as extern in header file
these variables are shared across multiple source files
*/

// define product database array
product db[MAX];

// define cart array
customer cart[MAX];

// define users array
account users[MAX];

// initialize product count to zero
int db_size = 0;

// initialize cart count to zero
int cart_size = 0;

// initialize user count to zero
int user_size = 0;

// initialize control flag
int flag = 0;

#ifdef USE_USB

// define uart file descriptor
int uart_fd;

// initialize mutex lock for thread synchronization
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

#endif
