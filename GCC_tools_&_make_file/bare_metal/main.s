	.cpu cortex-m4
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 1
	.eabi_attribute 30, 6
	.eabi_attribute 34, 1
	.eabi_attribute 18, 4
	.file	"main.c"
	.text
	.align	1
	.global	main
	.syntax unified
	.thumb
	.thumb_func
	.fpu softvfp
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	push	{r7}
	sub	sp, sp, #12
	add	r7, sp, #0
	ldr	r3, .L5
	ldr	r3, [r3, #24]
	ldr	r2, .L5
	orr	r3, r3, #8
	str	r3, [r2, #24]
	ldr	r3, .L5+4
	ldr	r3, [r3]
	ldr	r2, .L5+4
	orr	r3, r3, #256
	str	r3, [r2]
	ldr	r3, .L5+4
	ldr	r3, [r3]
	ldr	r2, .L5+4
	orr	r3, r3, #512
	str	r3, [r2]
	ldr	r3, .L5+4
	ldr	r3, [r3]
	ldr	r2, .L5+4
	bic	r3, r3, #1024
	str	r3, [r2]
	ldr	r3, .L5+4
	ldr	r3, [r3]
	ldr	r2, .L5+4
	bic	r3, r3, #2048
	str	r3, [r2]
.L4:
	ldr	r3, .L5+4
	ldr	r3, [r3, #12]
	ldr	r2, .L5+4
	eor	r3, r3, #4
	str	r3, [r2, #12]
	movs	r3, #0
	str	r3, [r7, #4]
	b	.L2
.L3:
	ldr	r3, [r7, #4]
	adds	r3, r3, #1
	str	r3, [r7, #4]
.L2:
	ldr	r3, [r7, #4]
	ldr	r2, .L5+8
	cmp	r3, r2
	ble	.L3
	b	.L4
.L6:
	.align	2
.L5:
	.word	1073876992
	.word	1073810432
	.word	999999
	.size	main, .-main
	.ident	"GCC: (GNU Tools for Arm Embedded Processors 7-2017-q4-major) 7.2.1 20170904 (release) [ARM/embedded-7-branch revision 255204]"
