# STM32 Basics – Bare-Metal Embedded Development

A collection of STM32 projects focused on low-level embedded systems development and direct hardware control through register-level programming.

The repository explores fundamental microcontroller peripherals and embedded programming concepts using bare-metal C, without relying on high-level abstraction libraries such as STM32 HAL.

Projects cover GPIO configuration, clock management, timers, interrupts, and peripheral interfacing, with an emphasis on understanding register configurations, bitwise operations, hardware behaviour, and timing calculations.

Each project includes code and technical documentation outlining the implementation, relevant hardware concepts, and configuration details.

## Projects

| Project | Description | Documentation |
|---|---|---|
| GPIO LED Blink | Basic GPIO configuration and direct register manipulation to control the onboard LED. | [LED Blink](./Blink/Blink.md) |
| Button-Controlled LED | GPIO input handling, button state detection, and LED control with software debouncing. | [Button-controlled LED](./InputBlink/InputBlink.md) |
| LED-Toggle | LED control with software debouncing, clocks and counters | [Toggled LED](./ToggleLED/ToggleLED.md) |