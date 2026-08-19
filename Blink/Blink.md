# STM32 GPIO LED BLINK
---

# Project Setup 
Add "STM32Cube\Repository\STM32Cube_FW_F4_V1.27.0\Drivers\CMSIS\Device\ST\STM32F4xx\Include" "STM32Cube\Repository\STM32Cube_FW_F4_V1.27.0\Drivers\CMSIS\Include" filepaths to include file allowing for use of hardware specific header file 

Find LED pin from datasheet 
![alt text](image.png)

# Planning

Since the pin is PA5, it is a pin belonging to GPIOA, so GPIOA needs to be enabled. For the GPIOA to be enabled, the GPIOA CLK needs to be enabled. 

Then the PA5 pin is set as an output. 

Now the pin can be ON and reset repeatedly in the for loop 100 times. 

# Bitmasking

&   AND
|   OR
~   NOT
<<  left shift
&=  AND Assignment
|=  OR Assignment


# Code

RCC controls the clocks of the preipheral. AHB1ENR repersts a memory adress that is the RCCs clock enable register specidically for the AHB1 pherhiperal
RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

![alt text](image-1.png)

The datasheet shows that the first bit is the GPIOA Enable, so this will be turned on with the RCC_AHB1ENR_GPIOAEN bitmask

GPIOA->MODER &= ~(3U << (5 * 2));

![alt text](image-2.png)

this shifts the value (11) which is (3)10 shifted by 10 bits. This resets all the bits for the 5th pin of the GPIO port

GPIOA->MODER |=  (1U << (5 * 2));

this shifts the value (11) which is (3)10 shifted by 10 bits. This sets the 5th pin of the GPIO port to 01 which is a digital output

GPIOA->OTYPER &= ~(1U << 5);

![alt text](image-3.png)

want default push pull operation of pin  so set to 0

GPIOA->OSPEEDR &= ~(3U << (5 * 2));

![alt text](image-4.png)

Determines speed of the pin, set to low speed with 00

GPIOA->PUPDR &= ~(3U << (5 * 2));

![alt text](image-5.png)

This sets the pin to have no pull up or pull down resistor, we would like to turn the pin on and off

Since we are only setting the pin to high, and low, we can user BSRR to turn the led on and off with a delay function to see the light turn off. removes the need to read the register

![alt text](image-6.png)

for(int i = 0;i<100;i++){
    GPIOA->BSRR = (1U << 5);       // PA5 HIGH
    delay(100000);

    GPIOA->BSRR = (1U << (5 + 16)); // PA5 LOW
    delay(100000);
};