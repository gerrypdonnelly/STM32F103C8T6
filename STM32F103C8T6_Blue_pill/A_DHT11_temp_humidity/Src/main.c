/**
 ******************************************************************************

DHT11 connected to PA0
Setting USART PA9 Tx
Setting USART PA10 Rx

Temperature and humidity data is read in and transmitted out over USART 2 at 115200
 ******************************************************************************
 */

#include<stdio.h>
#include "stm32f103xb.h"


#define DHT11_PIN       0  // PA0


#include <stdint.h>

// Delay function
void delay_us(uint32_t us) {
    volatile uint32_t count = (us * 9);  // Rough approximation for 72MHz
    while (count--) __asm__("nop");
}

// USART2 Initialization
void usart2_init(void) {
    RCC->APB2ENR |= (1 << 2);  // Enable GPIOA clock
    RCC->APB1ENR |= (1 << 17); // Enable USART2 clock

    // Configure PA2 as AF push-pull (USART2 TX)
    GPIOA->CRL &= ~(0xF << 8);
    GPIOA->CRL |= (0xB << 8);

    USART2->BRR = 0x271;  // 115200 baud at 72MHz
    USART2->CR1 |= (1 << 3) | (1 << 13);  // Enable TX, USART
}

// Send a character via USART2
void usart2_send_char(char c) {
    while (!(USART2->SR & (1 << 7)));  // Wait for TXE
    USART2->DR = c;
}

// Send a string via USART2
void usart2_send_string(char *str) {
    while (*str) {
        usart2_send_char(*str++);
    }
}

// Read data from DHT11
uint8_t dht11_read(uint8_t *humidity, uint8_t *temperature) {
    uint8_t data[5] = {0, 0, 0, 0, 0};

    // Request data
    GPIOA->CRL &= ~(0xF << (DHT11_PIN * 4));  // PA0 as output push-pull
    GPIOA->CRL |= (0x3 << (DHT11_PIN * 4));
    GPIOA->ODR &= ~(1 << DHT11_PIN);
    delay_us(18000);
    GPIOA->ODR |= (1 << DHT11_PIN);
    delay_us(30);

    // Switch to input mode
    GPIOA->CRL &= ~(0xF << (DHT11_PIN * 4));
    GPIOA->CRL |= (0x4 << (DHT11_PIN * 4));  // Input floating

    // Wait for response
    if ((GPIOA->IDR & (1 << DHT11_PIN))) return 0; // No response
    while (!(GPIOA->IDR & (1 << DHT11_PIN)));
    while (GPIOA->IDR & (1 << DHT11_PIN));

    // Read 40 bits
    for (int i = 0; i < 40; i++) {
        while (!(GPIOA->IDR & (1 << DHT11_PIN))); // Wait for high
        delay_us(30);
        if (GPIOA->IDR & (1 << DHT11_PIN))
            data[i / 8] |= (1 << (7 - (i % 8)));
        while (GPIOA->IDR & (1 << DHT11_PIN));
    }

    // Checksum
    if ((data[0] + data[1] + data[2] + data[3]) != data[4]) return 0;

    *humidity = data[0];
    *temperature = data[2];

    return 1;
}

int main(void) {
    usart2_init();

    uint8_t humidity, temperature;
    char buffer[32];

    while (1) {
        if (dht11_read(&humidity, &temperature)) {
            snprintf(buffer, sizeof(buffer), "Temp: %dC, Hum: %d%%\r\n", temperature, humidity);
            usart2_send_string(buffer);
        } else {
            usart2_send_string("DHT11 error!\r\n");
        }

        for (volatile uint32_t i = 0; i < 500000; i++); // Delay ~1s
    }
}
