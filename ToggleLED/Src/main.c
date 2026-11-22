#include <stdint.h>
#include <stdbool.h>
#include "stm32f446xx.h"
uint32_t previousRegValue;
uint32_t currentRegValue;
uint32_t pinRegMask;
uint16_t counterFlagMask;
volatile uint32_t milliseconds;
int DEBOUNCE_TIME = 100;


#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

	void TIM1_UP_TIM10_IRQHandler(void)
	{
		if (TIM1->SR & (1U << 0))
		{
			TIM1->SR &= ~(1U << 0);
			milliseconds++;
		}
	}

	int main(void){
			/*GPIO CLK*/
			RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
			RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
			RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
			/*Timer*/
			/* TIM1->PSC = 15999;
			TIM1->ARR = 999; 1 second blink*/
			TIM1->CR1 &= ~(1U << 0);
			TIM1->CR1 |= (0U << 1);
			TIM1->CR1 &= ~(1U << 3);
			TIM1->CR1 &= ~(1U << 4);
			TIM1->CR1 |= (1U << 7);
			TIM1->CR1 = (1U << 0);
			TIM1->SR = ~(1U << 0);
			TIM1->PSC = 15999;
			TIM1->ARR = 0;
			TIM1->DIER |= (1U << 0);
			NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn);
			TIM1->CR1 |= (1U << 0);
			/*Button*/
			GPIOC->MODER &= ~(3U << (13*2));
			GPIOC->PUPDR &= ~(3U << (13*2));
			/*LED*/
			GPIOA->MODER &= ~(3U << (5 * 2));
			GPIOA->MODER |=  (1U << (5 * 2));
			GPIOA->OTYPER &= ~(1U << 5);
			GPIOA->OSPEEDR &= ~(3U << (5 * 2));
			GPIOA->PUPDR &= ~(3U << (5 * 2));
			/* Turn on  I/O PC13 */
			/* turn on LED */
			/* turn on LED when PC13 is high */
			/* Loop forever */
			uint32_t previousButtonState = 0;
			uint32_t stableButtonState = 0;
			uint32_t lastTimeChange = 0;
			uint16_t counterFlagMask = (1U << 0);
			uint32_t pinRegMask = (1U << 13);

			while(true){
				uint32_t currentButtonState = GPIOC->IDR & pinRegMask;
				uint32_t currentTime = milliseconds;

			/*
				if(TIM1->SR & counterFlagMask){
					TIM1->SR = ~(1U << 0);
					GPIOA->ODR ^= (1U << 5);
				}
			Blink Code */
				if(currentButtonState && !previousButtonState){
					lastTimeChange = milliseconds;
				}
				if((currentTime - lastTimeChange) >= DEBOUNCE_TIME){
					if(currentButtonState != stableButtonState){
						stableButtonState = currentButtonState;
						if(stableButtonState){
							GPIOA->ODR ^= (1U << 5);
						}
					}
				}
				 previousButtonState = currentButtonState;
			}
};
