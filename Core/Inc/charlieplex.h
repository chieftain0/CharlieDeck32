#ifndef CHARLIEPLEX_H
#define CHARLIEPLEX_H

#include "stm32f1xx_hal.h"
#include <stdbool.h>

void Charlieplex_SetLED(GPIO_TypeDef **ports, int num_ports, uint16_t *pins, int num_pins, int x, int y, bool state);
void Charlieplex_Clear(GPIO_TypeDef **ports, int num_ports, uint16_t *pins, int num_pins);

#endif
