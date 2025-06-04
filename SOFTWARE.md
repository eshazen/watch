# Watch software

Initial software outline:

* Initialize RTC for 1 minute periodic interrupt
* Initialize AVR to go to sleep and wake on pin change interrupt from RTC
* On wakeup:  display time

Also need to provide some interface to set the time

## RTC

Basically working.  Time registers can be R/W and update as expected.

### Initialization

Set `TSPM[1:0] = 1` (nINTB output)

Set `INTA_enable` (addr 0x29) to `b'01000000'` (enable only periodic interrupt)

Set `Function` (addr 0x28) to `b'01000111'` (1 min periodic) -or-
<br> `b'00100111'` (1 sec periodic)

### Set / Read time

Time is in addresses 1-3 as BCD

### Interrupts

Setup AVR to interrupt on pin change on PC3.
Sleep to power-down mode and wake on interrupt.

Some example code:

```
set_sleep_mode(SLEEP_MODE_PWR_DOWN);
sleep_enable();
sleep_mode();
// wait for wake-up
sleep_disable();
power_all_enable();
```

## UART

UART working at 1200 baud (not 9600) with default 1MHz clock.

Need to find / recreate my_gets using the stdio hack.

## Display

It would be nice to display an analog clock face.
This is complicated by the fact that the E-Ink display
is 200x200 and we don't have enough RAM (200x200/8=5000 bytes)
for a bitmap.

One solution is a partial bitmap (e.g. 64x128 = 1k), and
a bit of code which takes a display list and iterates
over it 8 times, clipping the lines into regions,
sending each to the display as it completes.

    /---- 200 ------\
    +----+----+----+----+ \
    | 64 | 64 | 64 | 64 | |
	|    |    |    |    | |
	|    |    |    |    | |
	|    |    |    |    | 200 
    +----+----+----+----+ |
	|    |    |    |    | |
	|    |    |    |    | |
	|    |    |    |    | /
	|    |    |    |    |
    +----+----+----+----+

