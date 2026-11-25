#include <stdint.h>
#include <stdbool.h>
#include "stm32f446xx.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

void delay(volatile uint32_t count){

    while(count--){
        __asm volatile ("nop");
    }

}

void init(void){
	/*GPIO CLK*/
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	/*Timer*/
	TIM2->CCR1 = 100;
	// Configure PWM Mode 1
	TIM2->CCMR1 &= ~(7U << 4);
	TIM2->CCMR1 |=  (6U << 4);
	// Enable output compare preload
	TIM2->CCMR1 |= (1U << 3);
	// Enable Channel 1
	TIM2->CCER |= (1U << 0);
	// Enable auto-reload preload
	TIM2->CR1 |= (1U << 7);
	TIM2->PSC = 15;
	TIM2->ARR = 999;
	// Generate update event
	TIM2->EGR |= (1U << 0);
	// Start timer
	TIM2->CR1 |= (1U << 0);
	/*LED*/
	GPIOA->MODER &= ~(3U << (5 * 2));
	GPIOA->MODER |=  (2U << (5 * 2));
	GPIOA->OTYPER &= ~(1U << 5);
	GPIOA->OSPEEDR &= ~(3U << (5 * 2));
	GPIOA->PUPDR &= ~(3U << (5 * 2));

	GPIOA->AFR[0] &= ~(0xFU << (5 * 4));
	GPIOA->AFR[0] |=  (1U << (5 * 4));
};


int main(void){
	init();
	while(1){
		for(int i=0;i<20;i++){
			if(i<=10){
				TIM2->CCR1 = (i*10);
				delay(100000);
			}else{
				TIM2->CCR1 = (20-i)*10;
				delay(100000);
			}
		}
	}
};
