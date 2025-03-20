/**
 ******************************************************************************
Key PA0
LED PB2 APB2
Setting USART PA9 Tx
Setting USART PA10 Rx

Pressing '1' turns on the External LED all other keys turn it off.
 ******************************************************************************
 */

#include<stdio.h>
#include<stdint.h>
#include "stm32f103xb.h"
#include "UART.h"

#define GPIOBEN	(1U<<3)
#define GPIOB_2	(1U<<0)

#define LED_PIN GPIOB_2

char key;







int main(void)
{
	RCC->APB2ENR |= (1U<<3);
	//Set Mode of LED pin to output max speed 50Mhz
	GPIOB->CRL |=(1U<<0);
	GPIOB->CRL |=(1U<<1);
	//Set CNF of LED pin to Output push pull
	GPIOB->CRL &=~(1U<<2);
	GPIOB->CRL &=~(1U<<3);


	uart_Rx_interrupt_init();


  while (1)
    {


   	}
}



void uart_callback(void)
{
	key = USART1->DR;
			if(key=='1')
				  {
					  GPIOB->ODR |= LED_PIN;
				  }
				  else
				  {
					  GPIOB->ODR &=~LED_PIN;
				  }

}

void USART1_IRQHandler(void)
{
	//Check if Rx is set
	if(USART1->SR & USART_SR_RXNE)
	{
		//Do something
		uart_callback();
	}

}

