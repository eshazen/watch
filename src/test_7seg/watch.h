
// LEDs
#define LED_DDR DDRB
#define LED1_BIT 6
#define LED2_BIT 7
#define LED_PORT PORTB
#define LED_MASK (_BV(LED1_BIT)|_BV(LED2_BIT))

// buttons
#define SW1_DDR DDRC
#define SW1_BIT 2
#define SW1_PORT PORTC
#define SW1_PIN PINC

#define SW2_DDR DDRD
#define SW2_BIT 2
#define SW3_BIT 3
#define SW2_PORT PORTD
#define SW2_PIN PIND

#define SW1_PRESSED (SW1_PIN & _BV(SW1_BIT))
#define SW2_PRESSED (SW2_PIN & _BV(SW2_BIT))
#define SW3_PRESSED (SW2_PIN & _BV(SW3_BIT))

