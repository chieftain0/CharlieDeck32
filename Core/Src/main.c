#include "main.h"
#include "tim.h"
#include "usb_device.h"
#include "gpio.h"

#include "charlieplex.h"
#include "games.h"

#define BIT_WIDTH_TYPE(type) (sizeof(type) * 8)

void SystemClock_Config(void);
void Poll_Buttons(GPIO_TypeDef **ButtonPorts, uint16_t *ButtonPins, uint8_t NumButtons, uint8_t PressState, uint8_t *clickMap, uint8_t *pressMap);
static inline void seed_rng()

// USB variables
GPIO_TypeDef *usb_enum_pin_port = GPIOA;
uint16_t usb_enum_pin = GPIO_PIN_15;

// LED Matrix variables
GPIO_TypeDef *matrix_ports[] = {
    GPIOA, GPIOA, GPIOA, GPIOB, GPIOB, GPIOB, GPIOB, GPIOB,
    GPIOB, GPIOB, GPIOB, GPIOB, GPIOA, GPIOA, GPIOA, GPIOA};
#define NUM_MATRIX_PORTS (sizeof(matrix_ports) / sizeof(matrix_ports[0]))
#define TARGET_FPS 300

uint16_t matrix_pins[] = {
    GPIO_PIN_10, GPIO_PIN_9, GPIO_PIN_8, GPIO_PIN_15,
    GPIO_PIN_14, GPIO_PIN_13, GPIO_PIN_12, GPIO_PIN_11,
    GPIO_PIN_10, GPIO_PIN_2, GPIO_PIN_1, GPIO_PIN_0,
    GPIO_PIN_7, GPIO_PIN_6, GPIO_PIN_5, GPIO_PIN_4};
#define NUM_MATRIX_PINS (sizeof(matrix_pins) / sizeof(matrix_pins[0]))

#define NUM_ROWS_Y (NUM_MATRIX_PINS - 1)
#define NUM_COLUMNS_X (NUM_MATRIX_PINS)

uint8_t screen[NUM_ROWS_Y][NUM_COLUMNS_X] = {0};

// Button variables (External high pull-up)
static GPIO_TypeDef *button_ports[8] = {
    GPIOB, // 1 = UP
    GPIOB, // 2 = DOWN
    GPIOB, // 4 = LEFT
    GPIOB, // 8 = RIGHT
    GPIOA, // 16 = C
    GPIOA, // 32 = A
    GPIOA, // 64 = D
    GPIOA  // 128 = B
};
static uint16_t button_pins[8] = {
    GPIO_PIN_4, // 1 = UP
    GPIO_PIN_5, // 2 = DOWN
    GPIO_PIN_3, // 4 = LEFT
    GPIO_PIN_6, // 8 = RIGHT
    GPIO_PIN_1, // 16 = C
    GPIO_PIN_2, // 32= A
    GPIO_PIN_3, // 64 = D
    GPIO_PIN_0  // 128 = B
};
#define NUM_BUTTON_PORTS (sizeof(button_ports) / sizeof(button_ports[0]))
#define NUM_BUTTON_PINS (sizeof(button_pins) / sizeof(button_pins[0]))

#define BUTTON_UP (1 << 0)    // 0x01
#define BUTTON_DOWN (1 << 1)  // 0x02
#define BUTTON_LEFT (1 << 2)  // 0x04
#define BUTTON_RIGHT (1 << 3) // 0x08
#define BUTTON_C (1 << 4)     // 0x10
#define BUTTON_A (1 << 5)     // 0x20
#define BUTTON_D (1 << 6)     // 0x40
#define BUTTON_B (1 << 7)     // 0x80

// Mode variables
typedef enum
{
  MODE_MAIN_MENU = 0,
  MODE_SNAKE = 1,
  MODE_PONG = 2,
  MODE_FLAPPY = 3,
  MODE_TETRIS = 4,
  MODE_SCORE = 5
} GameMode;

GameMode mode = MODE_MAIN_MENU;

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_GPIO_Init();
  MX_USB_DEVICE_Init();

  HAL_TIM_Base_Start(&htim1);
  HAL_TIM_Base_Start(&htim2);
  HAL_TIM_Base_Start(&htim3);
  HAL_TIM_Base_Start(&htim4);

  Charlieplex_Clear(matrix_ports, NUM_MATRIX_PORTS, matrix_pins, NUM_MATRIX_PINS);

  HAL_GPIO_WritePin(usb_enum_pin_port, usb_enum_pin, GPIO_PIN_SET); // Initialize USB

  static unsigned long time_now = 0;
  time_now = HAL_GetTick();

  int score = 0;

  while (1)
  {
    uint8_t click_mask = 0;
    uint8_t press_mask = 0;
    Poll_Buttons(button_ports, button_pins, NUM_BUTTON_PORTS, GPIO_PIN_RESET, &click_mask, &press_mask);
    if (((click_mask & BUTTON_UP) || (click_mask & BUTTON_C)) && mode == MODE_MAIN_MENU)
    {
      seed_rng();
      mode = MODE_SNAKE;
    }
    else if (((click_mask & BUTTON_RIGHT) || (click_mask & BUTTON_B)) && mode == MODE_MAIN_MENU)
    {
      seed_rng();
      mode = MODE_PONG;
    }
    else if (((click_mask & BUTTON_DOWN) || (click_mask & BUTTON_A)) && mode == MODE_MAIN_MENU)
    {
      seed_rng();
      mode = MODE_FLAPPY;
    }
    else if (((click_mask & BUTTON_LEFT) || (click_mask & BUTTON_D)) && mode == MODE_MAIN_MENU)
    {
      seed_rng();
      mode = MODE_TETRIS;
    }

    switch (mode)
    {
    case MODE_MAIN_MENU:
      MainMenuMatrix(screen);
      break;
    case MODE_SNAKE:
      score = Play_Snake(screen, click_mask, (uint32_t)HAL_GetTick());
      if (score != -1)
      {
        mode = MODE_SCORE;
        time_now = HAL_GetTick();
      }

      break;
    case MODE_PONG:
      score = Play_Pong(screen, press_mask, (uint32_t)HAL_GetTick());
      if (score != -1)
      {
        mode = MODE_SCORE;
        time_now = HAL_GetTick();
      }

      break;
    case MODE_FLAPPY:
      score = Play_FlappyBird(screen, click_mask, (uint32_t)HAL_GetTick());
      if (score != -4)
      {
        mode = MODE_SCORE;
        time_now = HAL_GetTick();
      }

      break;
    case MODE_TETRIS:
      Play_Tetris(screen, click_mask);
      break;
    case 5:
      if (HAL_GetTick() - time_now < 3000)
      {
        ScoreMatrix(screen, score);
      }
      else
      {
        NVIC_SystemReset();
      }
      break;
    }
    Charlieplex_Display(matrix_ports, NUM_MATRIX_PORTS, matrix_pins, NUM_MATRIX_PINS, screen, (uint32_t)(TARGET_FPS / (NUM_ROWS_Y * NUM_COLUMNS_X)));
  }
}

/**
 * @brief Seeds the random number generator with the current time and the
 *        current counter value of timer 2. This should be called at the
 *        beginning of any game to ensure that the random numbers are
 *        different each time the game is played.
 */
static inline void seed_rng()
{
  srand(__HAL_TIM_GET_COUNTER(&htim2) ^ HAL_GetTick());
}

/**
 * @brief Polls an array of buttons, detects clicks and current press states.
 *
 * This function scans multiple buttons connected to GPIO pins, updates two bitmasks:
 * - **clickMap**: Bits set for buttons that transitioned from released to pressed
 *   during this polling cycle (rising edge detection).
 * - **pressMap**: Bits set for buttons that are currently pressed.
 *
 * @param[in]  ButtonPorts  Array of pointers to GPIO port structures for each button.
 * @param[in]  NumButtons   Number of buttons to scan (must be <= 8 for uint8_t maps).
 * @param[in]  ButtonPins   Array of GPIO pin numbers (HAL format) for each button.
 * @param[in]  PressState   Logical state representing a pressed button
 *                          (`GPIO_PIN_SET` or `GPIO_PIN_RESET`).
 * @param[out] clickMap     Pointer to a uint8_t that will store the click bitmask.
 *                          A bit is set if that button was newly pressed this cycle.
 * @param[out] pressMap     Pointer to a uint8_t that will store the press bitmask.
 *                          A bit is set if that button is currently pressed.
 *
 * @note Both bitmasks use bit position `i` for button index `i`.
 *       Example: If button 0 and 2 are pressed, pressMap = `0b00000101`.
 *
 * @warning NumButtons must not exceed 8 when using `uint8_t` maps. Increase the type
 *          if you need more buttons.
 *
 * @return None.
 */
void Poll_Buttons(GPIO_TypeDef **ButtonPorts, uint16_t *ButtonPins, uint8_t NumButtons, uint8_t PressState, uint8_t *clickMap, uint8_t *pressMap)
{
  if (NumButtons > BIT_WIDTH_TYPE(uint8_t))
  {
    *clickMap = 0;
    *pressMap = 0;
    return;
  }

  static uint8_t button_flags[BIT_WIDTH_TYPE(uint8_t)] = {0};
  uint8_t click_mask = 0;
  uint8_t press_mask = 0;

  for (uint8_t i = 0; i < NumButtons; i++)
  {
    GPIO_PinState state = HAL_GPIO_ReadPin(ButtonPorts[i], ButtonPins[i]);

    // Track continuous press state
    if (state == PressState)
    {
      press_mask |= (1 << i);
    }

    // Detect click (rising edge of press)
    if (state == PressState && button_flags[i] == 0)
    {
      button_flags[i] = 1;
      click_mask |= (1 << i);
    }
    else if (state != PressState && button_flags[i] == 1)
    {
      button_flags[i] = 0;
    }
  }

  *clickMap = click_mask;
  *pressMap = press_mask;
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_PLL_DIV1_5;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
