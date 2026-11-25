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

void GPIO_Init(void){
	/*GPIO CLK*/
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
	// Enable SYSCFG clock
	RCC->APB2ENR |= (1U << 14);
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
	SYSCFG->EXTICR[3] &= ~(0xFU << 4);  // Clear EXTI13 field
	SYSCFG->EXTICR[3] |=  (0x2U << 4);  // Select GPIOC
	EXTI->RTSR &= ~(1U << 13);
	EXTI->FTSR |=  (1U << 13);
	// Clear any existing pending interrupt
	EXTI->PR = (1U << 13);
	//Unmask EXTI13
	EXTI->IMR |= (1U << 13);
	// Enable EXTI15_10 in NVIC
	NVIC_EnableIRQ(EXTI15_10_IRQn);
}

void EXTI15_10_IRQHandler(void)
{
    if (EXTI->PR & (1U << 13))
    {
        // Clear pending interrupt flag
        EXTI->PR = (1U << 13);
        GPIOA->ODR ^= (1U << 5);
    }
}

int main(void)
{
    GPIO_Init();
    while (1)
    {
        // Main program continues running
    }
}
