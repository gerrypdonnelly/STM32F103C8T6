/*1.Entry Point */
ENTRY(Reset_Handler)



/*2. Memory Definitions*/
MEMORY
{
	FLASH(rx):ORIGIN = 0x08000000, LENGTH = 512k
	SRAM(rwx):ORIGIN = 0x20000000, LENGTH = 128k
}

_estack = ORIGIN(SRAM)+LENGTH(SRAM);

/*3. Indicate required heap and stack size*/

__max_heap_size = 0x200; 			/*converts to 512 decimal*/
__max_stack_size = 0x400; 			/*converts to 1024 decimal*/

/*Sections*/ 						/*common variables 6.36.1 gcc reference manual*/
SECTIONS
{
	/*First section of output file*/
	.text : 
	{
		. = ALIGN(4);
		*(.isr_vector_tbl)			/* merge all .isr_vector_tbl sections by using **/
		*(.text)					/* merge all .text sections by using **/
		*(.rodata)					/* merge all .rodata sections by using **/
		. = ALIGN(4);
		_etext = .;   				/*create a global symbol to hold end of text section */
	}>FLASH
	
	/*Second section of output file*/
	.data :
	{
		. = ALIGN(4);
		_sdata = .;					/*create a global symbol to hold start of data section*/
		*(.data)
		. = ALIGN(4);
		_edata = .;					/*create a global symbol to hold end of data section */
	}> SRAM AT> FLASH 				/*first places in flash but then loaded into SRAM ">(VMA) AT> (lam)"*/
	
	/*Third section of output file*/
	.bss :
	{
	. = ALIGN(4);
	_sbss = .; 						/*create a global symbol to hold start of bss section */
	*(.bss)							/*merge all .bss sections by using **/
	. = ALIGN(4);					/* To align eack location to t bytes*/
	_ebss = .;
	}> SRAM
}

/*(Merge) sections*/
