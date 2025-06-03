//
// read input from serial port with some editing
//    ^H or DEL = backspace
//    ^U        = delete line
// All other control characters ignored
// 
// buff - character array to store data up to nchar bytes
// always returns pointer to buff
//
// version for UART routines
//

#include "my_gets.h"
#include "uart.h"
#include <ctype.h>

char *my_gets( char *buff, int nchar) {
  char *p = buff;
  int n = 0;
  char c;
  while( 1) {
    //if( Serial.available()) {
    if( USART0CharacterAvailable()) {
      c = USART0ReceiveByte( NULL);
      // Serial.readBytes( ch, 1);
      // char c = ch[0];
      if( isprint(c)) {
        if( n < nchar) {
          *p++ = c;
          ++n;
          // Serial.write( c);
	  USART0SendByte( c, NULL);
        }
      }
      if( c == '\b' || c == '\177') {
        if( p > buff) {    // backspace?
          --p;
          --n;
//          Serial.write( '\b');
//          Serial.write( ' ');
//          Serial.write( '\b');
	  USART0SendByte( '\b', NULL);
	  USART0SendByte( ' ', NULL);
	  USART0SendByte( '\b', NULL);
        } else {
 //          Serial.write( '\a');
	  USART0SendByte( '\a', NULL);
        }
      }
      if( c == '\r' || c == '\n') {
        *p = '\0';
	  USART0SendByte( '\r', NULL);
	  USART0SendByte( '\n', NULL);
//        Serial.write( '\r');
//        Serial.write( '\n');
        return buff;
      }
    }
  }
}


