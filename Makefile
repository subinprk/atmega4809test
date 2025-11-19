MCU=atmega4809
CC=avr-gcc
CFLAGS=-mmcu=$(MCU) -Os -DF_CPU=16000000UL -mmcu=$(MCU) 
OBJCOPY=avr-objcopy
AVRDUDE=avrdude

PROGRAMMER=jtag2updi
PORT=COM4    # ← UNO가 잡힌 포트로 맞춰줘!

all: main.hex

main.elf: src/main.c
	$(CC) $(CFLAGS) -o $@ $<

main.hex: main.elf
	$(OBJCOPY) -O ihex -R .eeprom $< $@

flash: main.hex
	$(AVRDUDE) -p m4809 -c $(PROGRAMMER) -P $(PORT) -U flash:w:main.hex

clean:
	del main.elf main.hex 2> NUL || rm -f main.elf main.hex
