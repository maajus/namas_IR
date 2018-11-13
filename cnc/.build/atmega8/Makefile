


















.build/atmega8/src/main.o : src/main.c
	@echo src/main.c
	@mkdir -p .build/atmega8/src
	@/usr/bin/avr-gcc -mmcu=atmega8 -DF_CPU=8000000L -DARDUINO=105 -I/usr/share/arduino/hardware/arduino/cores/arduino -ffunction-sections -fdata-sections -g -Os -w -fno-use-cxa-atexit -I/usr/share/arduino/hardware/arduino/variants/standard   -o $@ -c src/main.c
include .build/atmega8/src/main.d















.build/atmega8/firmware.elf : .build/atmega8/src/main.o
	@echo Linking firmware.elf
	@/usr/bin/avr-gcc -mmcu=atmega8 -Wl,-Os -Wl,--gc-sections -o $@ $^ -lm


.build/atmega8/firmware.hex : .build/atmega8/firmware.elf
	@echo Converting to firmware.hex
	@/usr/bin/avr-objcopy -O ihex -R .eeprom $^ $@

include .build/atmega8/src/dependencies.d

all : .build/atmega8/firmware.hex
	@true

