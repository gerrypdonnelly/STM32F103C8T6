# Path : F:\MicroControllers\GCC_tools_&_make_file\linkerandstartup>
# $^ input files dosen't work in nmake
# $@ output file dosen't work in nmake

# once connected using telnet on 4444
# reset init 
# flash write_image erase stm32_blink.elf 
# reset init
# resume

# Problems
# works with nmake but not make
# telnet gives invalid host on 4444

#other questions relating to HKC
#What data is transfered between end devices and HUB?
#Is there a driver example?
#How to deal with the HAL file when transfering program to to run on an alternative device.


CC = arm-none-eabi-gcc
CC1 = arm-none-eabi-objcopy -O
CFLAGS = -c -mcpu=cortex-m3 -mthumb -std=gnu11
LDFLAGS =-nostdlib -T stm32_linker_script.ld -Wl,-Map=build/stm32_blink.map


all : bin/stm32_blink.elf

build/main.o : main.c
	$(CC) $(CFLAGS) main.c -o build/main.o

build/stm32f103_startup.o : stm32f103_startup.c
	$(CC) $(CFLAGS) stm32f103_startup.c -o build/stm32f103_startup.o

bin/stm32_blink.elf : build/main.o build/stm32f103_startup.o
	$(CC) $(LDFLAGS) build/*.o -o bin/stm32_blink.elf 
	$(CC1) binary bin/stm32_blink.elf bin/stm32_blink.bin
	$(CC1) srec bin/stm32_blink.elf bin/stm32_blink.s19 
	

load :
	
	openocd -f board/st_nucleo_f103rb.cfg

clean :
	rm build/*.o build/*.map bin/*.elf bin/*.bin bin/*.s19