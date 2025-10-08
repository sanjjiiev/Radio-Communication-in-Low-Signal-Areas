#include "stm32f4xx.h"

void sysTick_Delay(uint32_t ms){
    SysTick->LOAD = (ms*16000)-1;
    SysTick->VAL = 0;
    SysTick->CTRL = 5;
    while(!(SysTick->CTRL & (1<<16))){}
    SysTick->CTRL = 0;
}

int main(void) {
		RCC->AHB1ENR |= (1 << 0); 
		RCC->AHB1ENR |= (1 << 2); 	// Enable GPIOC
    RCC->APB2ENR |= (1 << 8);          // Enable ADC1
		GPIOC->MODER &= ~(3 << (13 * 2)); 
    GPIOC->MODER |=  (1 << (13 * 2)); 
    GPIOA->MODER |= (3 << (1 * 2));    // PA1 analog mode

    ADC1->SQR3 = 1;                    // Channel 1
    ADC1->CR2 |= (1 << 0);             // ADC ON

    uint16_t adc_value;

    while (1) {
        ADC1->CR2 |= (1 << 30);        // Start conversion
        while (!(ADC1->SR & (1 << 1))); //  Wait for EOC
        adc_value = ADC1->DR;          // 0–4095

				if (adc_value > 1000){
					GPIOC->ODR |= (1 << 13);
					sysTick_Delay(1);			
				}
				else {
					GPIOC->ODR &= ~(1 << 13);
				}	
			
    } 

}
