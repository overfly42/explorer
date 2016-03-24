avr-gcc  -Wall -Os -mmcu=attiny2313 -o blink.o  -c $1 
avr-gcc -Wall -Os -mmcu=attiny2313 blink.o -o blink.elf
avr-size --format=avr --mcu=attiny2313 blink.elf 
avr-objcopy -j .text -j .data -O ihex blink.elf blink.hex
sudo avrdude -c linuxspi -p t2313 -P /dev/spidev0.0 -U flash:w:./blink.hex 
