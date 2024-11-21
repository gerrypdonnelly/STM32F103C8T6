/*
 * Timer.c
 *
 *  Created on: Nov 11, 2024
 *      Author: gerdon
 *
 *      Time base generator
 *      Measure frequency of external event // Input capture mode
 *      Control an OP waveform or indicate hen period of time has elapsed //Output compare mode
 *      OPM one pulse mode started after stimulus and generate a pulse of programmed length after a programmed delay
 *
 *      Timx_CNT Current count value 32 16 bit depending on gp or advanced type
 *      TIMx_ARR Auto reload register counter restarts after counting up (by default) reaches value in auto reload register
 *      TIMx_PSC slows the counting speed by dividing down the system clock  AHB to HCLKto APB clk then to TIMx_PSC.  all dividers.
 *      Common registers
 *      PSC prescaler value
 *      ARR Auto reload register
 *      CR1 including enabling disabling timer
 *      SR checking state of timer flags setting and clearing flags
 *      CCR1,2,3,4 one for each channel
 *      CCM  configure capture compare functionality
 *      CCER  capture compare enable register
 */

#include "stm32f103xb.h"

#define TIM2EN (1U<<0)
#define TIM3EN (1U<<1)
#define CR1_CEN (1U<<0)
#define OC_TOGGLE (1U<<4 |1U<<5)
#define CCER_CC3E (1U<<8)
#define TIM4EN (1U<<2)
#define CCER_CC4E (1U<<12)


//Uses Timer2 to time out every one second 1Hz
void Tim2_1hz_init(void)
{
	RCC->APB1ENR |= TIM2EN;		//Enable clock access to timer 2
	TIM2->PSC =800 - 1;  		//Set pre-scaler value in pre-scaler register 8 000 000 /800 = 10000
	TIM2->ARR = 10000 - 1; 		//set auto reload value 10000/10000 = 1Hz
	TIM2->CNT = 0; 				//clear the counter value, write 0 into timer count register
	TIM2->CR1 |= CR1_CEN;		//enable the timer
}





void Tim3_PB0_output_compare(void)
{
	//PB0 is connected to TIM3_CH3 by default or can be re-mapped to TIM1_CH2

	//Enable clock access to GPIO B
	RCC->APB2ENR |=(1U<<3);
	//SET PB0 mode to "alternate" function mode
	//Set Mode of LED pin to output max speed 2Mhz
	GPIOB->CRL |=(1U<<1);
	GPIOB->CRL &=~(1U<<0);
		//Set CNF of LED pin to alternate function output push pull
	GPIOB->CRL |=(1U<<3);
	GPIOB->CRL &=~(1U<<2);


	RCC->APB1ENR |= TIM3EN;		//Enable clock access to timer 3
	TIM3->PSC =800 - 1;  		//Set pre-scaler value in pre-scaler register 8 000 000 /800 = 10000
	TIM3->ARR = 10000 - 1; 		//set auto reload value 10000/10000 = 1Hz

	TIM3->CCMR2 |=OC_TOGGLE;  //set bits 4 and 5 to 1 which toggles the output  Toggle - OC1REF toggles when TIMx_CNT=TIMx_CCR1. Set output compare toggle mode

	//enable channel 3 in compare mode
	TIM3->CCER |=CCER_CC3E;

	TIM3->CNT = 0; 				//clear the counter value, write 0 into timer count register
	TIM3->CR1 |= CR1_CEN;		//enable the timer
}






void Tim4_PB9_input_capture(void)
{
	//PB9 is connected to TIM4_CH4 by default this is physical pin 46

	//Enable clock access to GPIO B
	RCC->APB2ENR |=(1U<<3);

	//Configure the input pin
	//SET PB9 mode to "alternate" function mode
	//Set Mode of trace pin to input with pull up / down
	GPIOB->CRH |=(1U<<7);
	GPIOB->CRH &=~(1U<<6);
		//Set CNF of trace pin to Input mode
	//GPIOB->CRH &=~(1U<<5);
	//GPIOB->CRH &=~(1U<<4);
	//Enable pull up resistor
	GPIOB->ODR |= (1U<<9);

//Set alternate function if needed here//

	RCC->APB1ENR |= TIM4EN;		//Enable clock access to timer 4

	TIM4->PSC =800 - 1;  		//Set pre-scaler value in pre-scaler register 8 000 000 /800 = 10000
	//TIM4->ARR = 10000 - 1; 		//set auto reload value 10000/10000 = 1Hz

	TIM4->CCMR2 &=~(1U<<9);  //set bits 9 to 0 and 8 to 1 to 1 which CC4 channel is configured as input , IC4 is mapped to TI4
	TIM4->CCMR2 |=(1U<<8);

	//enable channel 4 in input mode
	TIM4->CCER |= CCER_CC4E;

	//TIM4->CNT = 0; 				//clear the counter value, write 0 into timer count register
	TIM4->CR1 |= CR1_CEN;		//enable the timer
}
