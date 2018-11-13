


















.build_ano/robotMotor/src/main.o : src/main.c
	@echo src/main.c
	@mkdir -p .build_ano/robotMotor/src
	@/usr/share/arduino/hardware/tools/avr/bin/avr-gcc -mmcu=atmega32u4 -DF_CPU=16000000L -DARDUINO=165 -DARDUINO_ARCH_AVR -I/usr/share/arduino/hardware/arduino/avr/cores/arduino -ffunction-sections -fdata-sections -g -Os -w -DUSB_VID=0x2341 -DUSB_PID=0x8039 -I/usr/share/arduino/hardware/arduino/avr/variants/robot_motor   -o $@ -c src/main.c
include .build_ano/robotMotor/src/main.d















.build_ano/robotMotor/firmware.elf : .build_ano/robotMotor/src/main.o
	@echo Linking firmware.elf
	@/usr/share/arduino/hardware/tools/avr/bin/avr-gcc -mmcu=atmega32u4 -Wl,-Os -Wl,--gc-sections -o $@ $^ -lm


.build_ano/robotMotor/firmware.hex : .build_ano/robotMotor/firmware.elf
	@echo Converting to firmware.hex
	@/usr/share/arduino/hardware/tools/avr/bin/avr-objcopy -O ihex -R .eeprom $^ $@

include .build_ano/robotMotor/src/dependencies.d

all : .build_ano/robotMotor/firmware.hex
	@true

