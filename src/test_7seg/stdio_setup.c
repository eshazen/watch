//
// this exists only because:
//    main must be c++ to use Statistics.h
//    the FDEV_SETUP_STREAM initializer violates various C++ rules

#include <stdio.h>
#include "uart.h"

// create a file pointer for read/write to USART0
FILE usart0_str = FDEV_SETUP_STREAM( USART0SendByte, USART0ReceiveByte, _FDEV_SETUP_RW);

