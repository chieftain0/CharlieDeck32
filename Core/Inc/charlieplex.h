#ifndef CHARLIEPLEX_H
#define CHARLIEPLEX_H

#include "main.h" // Needed for HAL

void Charlieplex_SetLED(GPIO_TypeDef **ports, int num_ports, uint16_t *pins, int num_pins, int x, int y, uint8_t state);
void Charlieplex_Clear(GPIO_TypeDef **ports, int num_ports, uint16_t *pins, int num_pins);
void Charlieplex_Display(GPIO_TypeDef **ports, int num_ports, uint16_t *pins, int num_pins, uint8_t matrix[num_pins - 1][num_pins], uint32_t pixel_delay_us);

void Delay_us(uint32_t us);
#endif
