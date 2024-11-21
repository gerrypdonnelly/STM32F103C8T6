/**
 ******************************************************************************
Key PA0
LED PB2 APB2
 ******************************************************************************
 */

#include "stm32f103xb.h"
#include <stdint.h>
const uint32_t delaysm = 215;       //Used as .rodata
const uint32_t delaymed = 16000;
const uint32_t delaylg = 27000000;


uint32_t led_size;	//Used as .bss
uint32_t led_length;


int main(void)
{
RCC->APB2ENR |=(1U<<3);//Enable clock to PB
//Set Mode of LED pin to output max speed 50Mhz
GPIOB->CRL |=(1U<<8);
GPIOB->CRL |=(1U<<9);
//Set CNF of LED pin to Output push pull
GPIOB->CRL &=~(1U<<10);
GPIOB->CRL &=~(1U<<11);

while(1)
{
	GPIOB->ODR ^=(1U<<2);
	for(int i =0; i < 1000000;i++){}

}
}

