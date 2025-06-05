#
# Makefile for Colorimeter on ATMega328
# "make fuse" once to set fuses on the MCU
# "make flash" to program using ISP or bootloader
#
#----- Choose a programmer here -----

# USB tiny programmer
# DUDEPORT  = -c usbtiny -P usb

# for AVRISP programmer on USB
DUDEPORT  = -c avrispv2 -P usb

# for Arduino bootloader
# DUDEPORT  = -c arduino -P /dev/ttyACM0

#-------------------- don't change things below here unless you know --------------------

MCU = atmega328
EXTRAOPT = -D__AVR_ATmega328P__ -DBAREMETAL

# 1 MHz for on-board oscillator with factory fuses
# F_OSC = 1000000

# 8 MHz for on-board oscillator
F_OSC = 8000000

# 16MHz for Stock arduino
# F_OSC = 16000000

# note that we need the float conversions in printf()
CFLAGS = -g -Os -mmcu=$(MCU) $(EXTRAOPT) -DF_CPU=$(F_OSC) -Wl,-u,vfprintf -lprintf_flt -lm
CPPFLAGS = -g -Os -mmcu=$(MCU) $(EXTRAOPT) -DF_CPU=$(F_OSC) -Wl,-u,vfprintf -lprintf_flt -lm -std=c++11

LDFLAGS = -Wl,-Map=$(<:.o=.map),--cref -mmcu=$(MCU) -Wl,-u,vfprintf,--print-memory-usage -lprintf_flt -lm

# turn off clock divide-by-8 (default lfuse value 0x62 --> 0xe2 for 328)
# clear EESAVE in hfuse      (default hfuse value 0xd9 --> 0xd1 for 328)
FUSEOPT = -U lfuse:w:0xe2:m -U hfuse:w:0xd1:m

# read fuses
RFUSEOPT = -U hfuse:r:-:h -U lfuse:r:-:h -U efuse:r:-:h

DUDEMCU = m328
AVRDUDE  = avrdude $(DUDEPORT) -p $(DUDEMCU) -y -u 

c_objects = spi.o ioport.o uart.o stdio_setup.o

cpp_objects = main.o epdif.o epd1in54_V2.o epdpaint.o imagedata.o

headers = epd1in54_V2.h  epdif.h  epdpaint.h  fonts.h  imagedata.h  ioport.h  seg7.h  spi.h watch.h uart.h

all: $(c_objects) $(cpp_objects)  main.hex list

clean:
	rm -f *.o *~ *.hex *.elf *.map *.lst lib/*.o

flash: main.hex
	$(AVRDUDE) -U flash:w:$^:i

list:
	avr-objdump -h -S main.elf > main.lst
	avr-size --common -x main.elf

$(c_objects): %.o: %.c $(headers)
	avr-gcc -c $(CFLAGS) $< -o $@

$(cpp_objects): %.o: %.cpp $(headers)
	avr-g++ -c $(CPPFLAGS) $< -o $@

main.elf: $(c_objects) $(cpp_objects)
	avr-g++ $(LDFLAGS) $(c_objects) $(cpp_objects) -o $@

main.hex: main.elf
	avr-objcopy -j .text -j .data -O ihex $< $@
fuse:
	$(AVRDUDE) $(FUSEOPT)

rfuse:
	$(AVRDUDE) $(RFUSEOPT)
