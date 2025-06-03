#
# Makefile for blinky
#

MAIN = main_uart

# MCU = attiny85
MCU = atmega328

F_OSC = 1000000
# 8 MHz for on-board oscillator
# F_OSC = 8000000

# 16MHz for Stock arduino
# F_OSC = 16000000

CFLAGS = -g -Os -mmcu=$(MCU) $(EXTRAOPT) -DF_CPU=$(F_OSC) -Wl,-u,vfprintf -lprintf_min -lm
# no-optimization settings for interrupt code
CFLAGS_NOOPT = -g -O0 -mmcu=$(MCU) $(EXTRAOPT) -DF_CPU=$(F_OSC) -I../util -Wl,-u,vfprintf -lprintf_min

LDFLAGS = -Wl,-Map=$(<:.o=.map),--cref -mmcu=$(MCU)

FUSEOPT = -U hfuse:w:0xd9:m

# programmer configuration for avrdude programming utility

# for AVRISP programmer on USB
DUDEPORT  = -c avrispv2 -P usb

# for Arduino bootloader
# DUDEPORT  = -c arduino -P /dev/ttyACM0

DUDEMCU = m328
# DUDEMCU = t85
AVRDUDE  = avrdude $(DUDEPORT) -p $(DUDEMCU) -y -u 

objects = ${MAIN}.o uart.o parse.o my_gets.o i2c.o

headers =

all: $(objects)  ${MAIN}.hex list

clean:
	rm -f *.o *~ *.hex *.elf *.map *.lst

flash: ${MAIN}.hex
	$(AVRDUDE) -U flash:w:$^:i

list:
	avr-objdump -h -S ${MAIN}.elf > ${MAIN}.lst
	avr-size --common -x ${MAIN}.elf

$(objects): %.o: %.c $(headers)
	avr-gcc -c $(CFLAGS) $< -o $@

${MAIN}.elf: $(objects)
	avr-gcc $(LDFLAGS) $(objects) -o $@

${MAIN}.hex: ${MAIN}.elf
	avr-objcopy -j .text -j .data -O ihex $< $@

fuse:
	$(AVRDUDE) $(FUSEOPT)
