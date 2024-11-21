hold down shift, right click and open command prompt
F:\MicroControllers\GCC_tools_&_make_file\bare_metal>
in ref manual section 3.2 Options controlling kind of output
-c compile and assemble but dont link
-o output
arm-none-eabi-gcc -c main.c -o main.o
in ref manual section 3.19.5 Options controlling kind of ARM device
STM32F103C8T6 uses cortex m3 core 64k/20k
cortex m use thumb not arm
arm-none-eabi-gcc -c -mcpu=cortex-m4 -mthumb main.c -o main.o

-S stop after compilation do not assemble
arm-none-eabi-gcc -S -mcpu=cortex-m4 -mthumb main.c -o main.s
this can be viewed as assembly language

Object jump tool
arm-none-eabi-objdump //to see flag options
arm-none-eabi-objdump -x main.o
arm-none-eabi-objdump -g main.o
arm-none-eabi-objdump -D main.o   //dissassembly
arm-none-eabi-objdump -d main.o  //dissassembly just code .text section

output can be piped 
arm-none-eabi-objdump -D main.o > disassem

Memory and boot sequence
FLASH 0x0800 0000
includes vector table located at 0x0800 0004
SRAM read and write starts at 0x2000 0000
includes variables and stack

linker script specifies the memory layout and initializes the memory sections used by the firmware
memory layout
Section definitions
Options   eg entry point
Symbols

MEMORY
Types of memory and locations
name {(attr)] : ORIGIN = origin, LENGTH = len
e.g.
FLASH(rx) : ORIGIN = 0x08000000,LENGTH = 512k
SRAM(rwx):ORIGIN = 0x20000000,LENGTH=128k


SECTIONS
{

}
e.g.
SECTIONS
{
	.text:
	{
	*(.text) /*merge all .text sections of input files*/
	}> FLASH
}

.text placed in flash
.data placed in sram
.bss placed in sram

STARTUP CODE
1. Reset handler (startupcode)
copies initial values of variables from FLASH to SRAM
zeros unitialized data portion of SRAM

2. Interrupt vector table
array of addressed of interrupt handler functions
every required vector is assigned an overideable _weak slias to a default function that loops forever

LMA load memory address
VMA virtual memory address

Flash memory
.data
.rodata
.text
.isr_vector_tbl
NOTE (.bss is stored in SRAM directly)



Linking
linker documentation 
arm-none-eabi-gcc -nostdlib -T stm32_linker_script.ld *.o -o stm32_blink.elf    //Takes all the .o files 
