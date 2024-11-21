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
CFLAGS = -c -mcpu=cortex-m3 -mthumb -std=gnu11
LDFLAGS =-nostdlib -T stm32_linker_script.ld -Wl,-Map=stm32_blink.map


all : stm32_blink.elf

main.o : main.c
	arm-none-eabi-gcc -c -mcpu=cortex-m3 -mthumb -std=gnu11 main.c -o main.o

stm32f103_startup.o : stm32f103_startup.c
	arm-none-eabi-gcc -c -mcpu=cortex-m3 -mthumb -std=gnu11 stm32f103_startup.c -o stm32f103_startup.o

stm32_blink.elf : main.o stm32f103_startup.o
	arm-none-eabi-gcc -nostdlib -T stm32_linker_script.ld *.o -o stm32_blink.elf -Wl,-Map=stm32_blink.map  

load :
	openocd -f board/st_nucleo_f103rb.cfg

clean :
	rmdir -r out