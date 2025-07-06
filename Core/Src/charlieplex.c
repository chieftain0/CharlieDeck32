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
 * @param state uint8_t value indicating the desired state of the LED:
 *              - 1: Turn the LED on.
 *              - 0: Turn the LED off.
 *
 * @note The indexes start at 0. Ensure that the number of ports matches the number of pins.
 *       This function will configure the pins as outputs to set the LED state to ON,
 *       and as inputs to set the LED state to OFF.
 */
void Charlieplex_SetLED(GPIO_TypeDef **ports, int num_ports, uint16_t *pins, int num_pins, int x, int y, uint8_t state)
{
    if (num_ports != num_pins)
    {
        return;
    }
    if (x < 0 || x > num_ports || y < 0 || y > num_ports - 1)
    {
        return;
    }

    int x_int = x;
    int y_int = y;
    if (y_int >= x_int)
    {
        y_int += 1;
    }

    GPIO_InitTypeDef GPIO_InitStruct = {0};

    if (state)
    {
        GPIO_InitStruct.Pin = pins[x_int];
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(ports[x_int], &GPIO_InitStruct);
        HAL_GPIO_WritePin(ports[x_int], pins[x_int], GPIO_PIN_SET);

        GPIO_InitStruct.Pin = pins[y_int];
        HAL_GPIO_Init(ports[y_int], &GPIO_InitStruct);
        HAL_GPIO_WritePin(ports[y_int], pins[y_int], GPIO_PIN_RESET);
    }
    else
    {
        GPIO_InitStruct.Pin = pins[x_int];
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        HAL_GPIO_Init(ports[x_int], &GPIO_InitStruct);
        GPIO_InitStruct.Pin = pins[y_int];
        HAL_GPIO_Init(ports[y_int], &GPIO_InitStruct);
    }
}

/**
 * @brief Display a matrix on a Charlieplexed LED array.
 *
 * @param ports Array of GPIO ports associated with each pin.
 * @param num_ports Number of GPIO ports in the ports array.
 * @param pins Array of pin numbers corresponding to each port.
 * @param num_pins Number of pin numbers in the pins array.
 * @param matrix 2D array of uint8_t values representing the desired state of each LED in the array.
 * @param pixel_delay Time in milliseconds to delay between setting each LED state.
 *
 * @note The matrix is indexed as follows: matrix[row][column]. The indexes start at 0.
 *       The number of rows in the matrix must be one less than num_pins.
 *       The number of columns in the matrix must be equal to num_pins.
 *
 * @warning This function is blocking. Use with caution.
 */
void Charlieplex_Display(GPIO_TypeDef **ports, int num_ports, uint16_t *pins, int num_pins, uint8_t matrix[num_pins - 1][num_pins], unsigned long pixel_delay)
{
    for (int i = 0; i < num_pins - 1; i++)
    {
        for (int j = 0; j < num_pins; j++)
        {
            Charlieplex_SetLED(ports, num_ports, pins, num_pins, j, i, matrix[i][j]);
            Delay_us(pixel_delay);
            Charlieplex_SetLED(ports, num_ports, pins, num_pins, j, i, 0);
        }
    }
}

void Delay_us(unsigned long us)
{
    unsigned long start = TIM1->CNT;
    while (TIM1->CNT - start < us)
    {
    }
}