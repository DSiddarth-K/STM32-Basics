
#include <stdint.h>
#include <stdbool.h>
#include "stm32f446xx.h"
uint32_t pinRegMask;

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

int main(void)
{
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
	/* Turn on  I/O PC13 */
	/* turn on LED */
	/* turn on LED when PC13 is high */
    /* Loop forever */
	while(true){
		uint32_t pinRegMask = (1U << 13);
	    if(GPIOC->IDR & pinRegMask)
	    	GPIOA->BSRR = (1U << (5 + 16));       // PA5 HIGH
	    else{
	    	GPIOA->BSRR = (1U << 5);// PA5 LOW
	    }
	};
}
