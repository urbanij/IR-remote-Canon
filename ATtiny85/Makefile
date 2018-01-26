# Name: Makefile
# Author: <insert your name here>
# Copyright: <insert your copyright message here>
# License: <insert your license reference here>

# DEVICE ....... The AVR device you compile for
# CLOCK ........ Target AVR clock rate in Hertz
# OBJECTS ...... The object files created from your source files. This list is
#                usually the same as the list of source files with suffix ".o".
# PROGRAMMER ... Options to avrdude which define the hardware you use for
#                uploading to the AVR and the interface where this hardware
#                is connected.
# FUSES ........ Parameters for avrdude to flash the fuses appropriately.

DEVICE     = attiny85
CLOCK      = 1000000

# -------------------------------------------------------------- #
# uncomment the right one:
# Mac:
PROGRAMMER = -c arduino -P /dev/tty.usbmodemFA131 -b 19200
# Windows:
# PROGRAMMER = -c arduino -P COM3 -b 19200
# Ubuntu:
# PROGRAMMER = -c arduino -P /dev/ttyACM0 -b 19200
# -------------------------------------------------------------- #


OBJECTS    = shoot.o
FUSES      = -U lfuse:w:0x62:m -U hfuse:w:0xdf:m -U efuse:w:0xff:m

######################################################################
######################################################################

# Tune the lines below only if you know what you are doing:

AVRDUDE = avrdude $(PROGRAMMER) -p $(DEVICE)
# COMPILE = avr-gcc -Wall -Os -DF_CPU=$(CLOCK) -mmcu=$(DEVICE)

# added -std=c99
COMPILE = avr-gcc -Wall -std=c99 -Os -DF_CPU=$(CLOCK) -mmcu=$(DEVICE) 

# symbolic targets:
all:   shoot.hex

.c.o:
	$(COMPILE) -c $< -o $@

.S.o:
	$(COMPILE) -x assembler-with-cpp -c $< -o $@
# "-x assembler-with-cpp" should not be necessary since this is the default
# file type for the .S (with capital S) extension. However, upper case
# characters are not always preserved on Windows. To ensure WinAVR
# compatibility define the file type manually.

.c.s:
	$(COMPILE) -S $< -o $@

flash:	all
	$(AVRDUDE) -U flash:w:shoot.hex:i

fuse:
	$(AVRDUDE) $(FUSES)

install: flash fuse

# if you use a bootloader, change the command below appropriately:
load: all
	bootloadHID shoot.hex

clean:
	rm -f shoot.hex shoot.elf $(OBJECTS)

# file targets:
shoot.elf: $(OBJECTS)
	$(COMPILE) -o shoot.elf $(OBJECTS)

shoot.hex: shoot.elf
	rm -f shoot.hex
	avr-objcopy -j .text -j .data -O ihex shoot.elf shoot.hex
# If you have an EEPROM section, you must also create a hex file for the
# EEPROM and add it to the "flash" target.

# Targets for code debugging and analysis:
disasm:	shoot.elf
	avr-objdump -d shoot.elf

cpp:
	$(COMPILE) -E shoot.c
