// include uart header file
#include "uart.h"

// compile this section only if usb is enabled
#ifdef USE_USB

// function to configure uart settings like baud rate and flags
int uart_configure(int fd)
{
    // declare structure for terminal options
    struct termios opt;

    // get current uart attributes
    if(tcgetattr(fd,&opt)!=0){
        // print error if failed
        perror("tcgetattr");
        // return error
        return -1;
    }

    // set input baud rate to 9600
    cfsetispeed(&opt,B9600);

    // set output baud rate to 9600
    cfsetospeed(&opt,B9600);

    // enable receiver and set local mode
    opt.c_cflag |= (CLOCAL | CREAD);

    // disable parity bit
    opt.c_cflag &= ~PARENB;

    // set one stop bit
    opt.c_cflag &= ~CSTOPB;

    // clear current data size bits
    opt.c_cflag &= ~CSIZE;

    // set data size to 8 bits
    opt.c_cflag |= CS8;

    // disable canonical mode and signals
    opt.c_lflag = 0;

    // disable input processing
    opt.c_iflag = 0;

    // disable output processing
    opt.c_oflag = 0;

    // apply settings immediately
    return tcsetattr(fd,TCSANOW,&opt);
}

// end of usb conditional compilation
#endif

// function to read data from uart until delimiter or size limit
int uart_readline(char *buf, int size)
{
#ifdef USE_USB

    // initialize index counter
    int i = 0;

    // declare variable to store incoming character
    char c;

    // loop until buffer limit is reached
    while(i < size - 1)
    {
        // read one byte from uart
        int n = read(uart_fd, &c, 1);

        // break if read fails
        if(n <= 0) break;

        // break if delimiter found
        if(c == '$') break;

        // skip newline and carriage return
        if(c == '\r' || c == '\n') continue;

        // store character in buffer
        buf[i++] = c;
    }

    // terminate string with null character
    buf[i] = '\0';

    // return number of characters read
    return i;

#else

    // prompt user for input
    printf("Enter Input: ");

    // flush output buffer
    fflush(stdout);

    // read input from standard input
    if(fgets(buf, size, stdin) == NULL)

        // return zero if input fails
        return 0;

    // remove newline character from input
    buf[strcspn(buf, "\n")] = '\0';

    // return length of input string
    return strlen(buf);

#endif
}

// function to send message through uart or console
void uart_send(const char *msg)
{
#ifdef USE_USB

    // write message to uart
    write(uart_fd, msg, strlen(msg));

#else

    // print message to console
    printf("%s", msg);

#endif
}