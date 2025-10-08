#include "stm32f4xx.h"

void sysTick_Delay(uint32_t ms){
    SysTick->LOAD = (ms*16000)-1;
    SysTick->VAL = 0;
    SysTick->CTRL = 5;
    while(!(SysTick->CTRL & (1<<16))){}
    SysTick->CTRL = 0;
}

int main(void){
    RCC->AHB1ENR |= (1<<0);  
    GPIOA->MODER &= ~(3 << 0);  // PA0 input
    GPIOA->PUPDR |=  (1 << 0);	// Enable GPIOA
    GPIOA->MODER |= (1<<10);      // PA5 output (TX)
    int send=0;
    while(1){
			  send = send+0;
        if ((GPIOA->IDR & (1 << 0)) == 0){
				send=send+1; 
        sysTick_Delay(100);
				}					// Built-in button pressed once
        if(send == 1){
            GPIOA->ODR ^= (1<<5);               // Transmit square wave
            sysTick_Delay(200);
        }
				if(send == 2){
            GPIOA->ODR ^= (1<<5);               // Transmit square wave
            sysTick_Delay(600);
        }
				if(send >= 3){
            GPIOA->ODR ^= (1<<5);               // Transmit square wave
            sysTick_Delay(1000);
        }
    }
}
