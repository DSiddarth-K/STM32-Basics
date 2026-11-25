# STM32 GPIO LED With Button Input

# Project Setup 
First an STM32 project was created. Missing include files were added from the following filepaths:
"STM32Cube\Repository\STM32Cube_FW_F4_V1.27.0\Drivers\CMSIS\Device\ST\STM32F4xx\Include" "STM32Cube\Repository\STM32Cube_FW_F4_V1.27.0\Drivers\CMSIS\Include" 

Including these file path in the project lets us use the hardware specific header file that contains all the register adresses.

# Code

A similar process from the Blink project is used to setup the LED. The user manual identifies PC13 as avilable as a push button. The clock for GPIO C port is turned on, the mode is set to input with a BITMASK. No pull-up/pull-down resistor is configured on the register.

```
RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
GPIOC->MODER &= ~(3U << (13*2));
GPIOC->PUPDR &= ~(3U << (13*2));
```

uint32_t is a C data type that represents an unsigned 32-bit integer. This datatype can be used to create a 32-bit variable that to use as a bitmask because STM32F446RE peripherals are 32 bits wide. The input data register is read by using the AND operator with a bitmask to read the 13th register which is connected to the button. 

```
uint32_t pinRegMask;
while(true){
		uint32_t pinRegMask = (1U << 13);
	    if(GPIOC->IDR & pinRegMask)
	    	GPIOA->BSRR = (1U << (5 + 16));       
	    else{
	    	GPIOA->BSRR = (1U << 5);
	    }
	};
```