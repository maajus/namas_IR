


























.build_ano/pro/src/main.o : src/main.cpp
	@echo src/main.cpp
	@mkdir -p .build_ano/pro/src
	@/usr/share/arduino/hardware/tools/avr/bin/avr-g++ -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=165 -DARDUINO_ARCH_AVR -I/usr/share/arduino/hardware/arduino/avr/cores/arduino -ffunction-sections -fdata-sections -g -Os -w -I/usr/share/arduino/hardware/arduino/avr/variants/eightanaloginputs -fno-exceptions  -o $@ -c src/main.cpp
include .build_ano/pro/src/main.d







.build_ano/pro/firmware.elf : .build_ano/pro/src/main.o
	@echo Linking firmware.elf
	@/usr/share/arduino/hardware/tools/avr/bin/avr-gcc -mmcu=atmega328p -Wl,-Os -Wl,--gc-sections -o $@ $^ -lm


.build_ano/pro/firmware.hex : .build_ano/pro/firmware.elf
	@echo Converting to firmware.hex
	@/usr/share/arduino/hardware/tools/avr/bin/avr-objcopy -O ihex -R .eeprom $^ $@

include .build_ano/pro/src/dependencies.d

all : .build_ano/pro/firmware.hex
	@true

