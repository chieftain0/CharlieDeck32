#include "charlieplex.h"
#include "main.h"

/**
 * @brief Sets all pins of the charlieplexed array to input mode without pullup/pulldown.
 *        This is useful for clearing the array of all active LEDs.
 *
 * @param ports Array of GPIO ports to address.
 * @param num_ports Number of GPIO ports in the ports array.
 * @param pins Array of pin numbers to address on the GPIO ports.
 * @param num_pins Number of pin numbers in the pins array.
 */
void Charlieplex_Clear(GPIO_TypeDef **ports, int num_ports, uint16_t *pins, int num_pins)
{
    if (num_ports != num_pins)
    {
        return;
    }

    GPIO_InitTypeDef GPIO_InitStruct = {0};

    for (int i = 0; i < num_ports; i++)
    {
        GPIO_InitStruct.Pin = pins[i];
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        HAL_GPIO_Init(ports[i], &GPIO_InitStruct);
    }
}

/**
 * @brief Controls the state of a specific LED in a Charlieplexed LED array.
 *
 * @param ports Array of GPIO ports associated with each pin.
 * @param num_ports Number of GPIO ports in the ports array.
 * @param pins Array of pin numbers corresponding to each port.
 * @param num_pins Number of pin numbers in the pins array.
 * @param x (Horizontal) Index representing the first pin controlling the LED.
 * @param y (Vertical) Index representing the second pin controlling the LED.
 * @param state Boolean value indicating the desired state of the LED:
 *              - true: Turn the LED on.
 *              - false: Turn the LED off.
 *
 * @note The indexes start at 0. Ensure that the number of ports matches the number of pins.
 *       This function will configure the pins as outputs to set the LED state to ON,
 *       and as inputs to set the LED state to OFF.
 */
void Charlieplex_SetLED(GPIO_TypeDef **ports, int num_ports, uint16_t *pins, int num_pins, int x, int y, bool state)
{
    if (num_ports != num_pins)
    {
        return;
    }
    if (x < 0 || x > num_ports || y < 0 || y > num_ports - 1)
    {
        return;
    }

    GPIO_InitTypeDef GPIO_InitStruct = {0};

    if (state)
    {
        GPIO_InitStruct.Pin = pins[x];
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(ports[x], &GPIO_InitStruct);
        HAL_GPIO_WritePin(ports[x], pins[x], GPIO_PIN_SET);

        GPIO_InitStruct.Pin = pins[y + 1];
        HAL_GPIO_Init(ports[y + 1], &GPIO_InitStruct);
        HAL_GPIO_WritePin(ports[y + 1], pins[y + 1], GPIO_PIN_RESET);
    }
    else
    {
        GPIO_InitStruct.Pin = pins[x];
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        HAL_GPIO_Init(ports[x], &GPIO_InitStruct);
        GPIO_InitStruct.Pin = pins[y + 1];
        HAL_GPIO_Init(ports[y + 1], &GPIO_InitStruct);
    }
}
