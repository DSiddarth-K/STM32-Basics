#include <stdint.h>
#include <stdbool.h>
#include "stm32f446xx.h"
uint32_t previousRegValue;
uint32_t currentRegValue;
uint32_t pinRegMask;
uint16_t counterFlagMask;
volatile uint32_t milliseconds;



#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

	int main(void){
			/*GPIO CLK*/
			RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
			RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
			/*Button*/
			GPIOC->MODER &= ~(3U << (13*2));
			GPIOC->PUPDR &= ~(3U << (13*2));
			/*LED*/
			GPIOA->MODER &= ~(3U << (5 * 2));
			GPIOA->MODER |=  (1U << (5 * 2));
			GPIOA->OTYPER &= ~(1U << 5);
			GPIOA->OSPEEDR &= ~(3U << (5 * 2));
			GPIOA->PUPDR &= ~(3U << (5 * 2));
			/*Interrupt*/
			SYSCFG_EXTICR4 &= ~(15U << 4);
			uint32_t previousButtonState = 0;
			uint32_t pinRegMask = (1U << 13);

			while(true){
				uint32_t currentButtonState = GPIOC->IDR & pinRegMask;
				if(currentButtonState && !previousButtonState){
					GPIOA->ODR ^= (1U << 5);
				}
				 previousButtonState = currentButtonState;
			}
};
