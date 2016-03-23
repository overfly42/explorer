avr-gcc  -Wall -Os -mmcu=attiny2313 -o blink.o  -c blink.c 
avr-gcc -Wall -Os -mmcu=attiny2313 blink.o -o blink.elf
avr-objcopy -j .text -j .data -O ihex blink.elf blink.hex
sudo avrdude -c linuxspi -p t2313 -P /dev/spidev0.0 -U flash:w:./blink.hex 
