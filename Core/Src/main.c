#include "main.h"

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;
PCD_HandleTypeDef hpcd_USB_FS;

void SystemClock_Config(void);
static void MX_TIM1_Init(void);
static void MX_TIM2_Init(void);
static void MX_GPIO_Init(void);
static void MX_USB_PCD_Init(void);

uint8_t Poll_Buttons(GPIO_TypeDef **ButtonPorts, int NumPorts, uint16_t *ButtonPins, int NumPins, uint8_t PressState);

// USB variables
GPIO_TypeDef *usb_enum_pin_port = GPIOA;
uint16_t usb_enum_pin = GPIO_PIN_15;

// LED Matrix variables
GPIO_TypeDef *matrix_ports[] = {
    GPIOA, GPIOA, GPIOA, GPIOB, GPIOB, GPIOB, GPIOB, GPIOB,
    GPIOB, GPIOB, GPIOB, GPIOB, GPIOA, GPIOA, GPIOA, GPIOA};
#define NUM_MATRIX_PORTS (sizeof(matrix_ports) / sizeof(matrix_ports[0]))

uint16_t matrix_pins[] = {
    GPIO_PIN_10, GPIO_PIN_9, GPIO_PIN_8, GPIO_PIN_15,
    GPIO_PIN_14, GPIO_PIN_13, GPIO_PIN_12, GPIO_PIN_11,
    GPIO_PIN_10, GPIO_PIN_2, GPIO_PIN_1, GPIO_PIN_0,
    GPIO_PIN_7, GPIO_PIN_6, GPIO_PIN_5, GPIO_PIN_4};
#define NUM_MATRIX_PINS (sizeof(matrix_pins) / sizeof(matrix_pins[0]))

uint8_t screen[NUM_MATRIX_PINS - 1][NUM_MATRIX_PINS] = {0};

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

// Mode variables
int mode = 0;
// 0 = Main Menu, 1 = Snake (UP, C), 2 = Ping Pong (RIGHT, B),
// 3 = Flappy Bird (DOWN, A), 4 = Tetris (LEFT, D), 5 = Show Score

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
  MX_GPIO_Init();
  MX_USB_PCD_Init();

  HAL_TIM_Base_Start(&htim1);
  HAL_TIM_Base_Start(&htim2);
  Charlieplex_Clear(matrix_ports, NUM_MATRIX_PORTS, matrix_pins, NUM_MATRIX_PINS);

  srand(__HAL_TIM_GET_COUNTER(&htim2)); // Temporary seed move to

  static unsigned long time_now = 0;
  time_now = HAL_GetTick();

  int score = 0;

  while (1)
  {
    uint8_t button_mask = Poll_Buttons(button_ports, NUM_BUTTON_PORTS, button_pins, NUM_BUTTON_PINS, 0);
    if (((button_mask & 1) || (button_mask & 16)) && mode == 0)
    {
      mode = 1;
      srand(__HAL_TIM_GET_COUNTER(&htim2));
    }
    else if (((button_mask & 8) || (button_mask & 128)) && mode == 0)
    {
      mode = 2;
      srand(__HAL_TIM_GET_COUNTER(&htim2));
    }
    else if (((button_mask & 2) || (button_mask & 32)) && mode == 0)
    {
      mode = 3;
      srand(__HAL_TIM_GET_COUNTER(&htim2));
    }
    else if (((button_mask & 4) || (button_mask & 64)) && mode == 0)
    {
      mode = 4;
      srand(__HAL_TIM_GET_COUNTER(&htim2));
    }

    switch (mode)
    {
    case 0:
      MainMenuMatrix(screen);
      break;
    case 1:
      Play_Snake(screen, button_mask, rand(), rand(), (uint32_t)HAL_GetTick());

      break;
    case 2:
      Play_Pong(screen, button_mask);

      break;
    case 3:
      score = Play_FlappyBird(screen, button_mask, rand(), (uint32_t)HAL_GetTick());
      if (score != -4)
      {
        mode = 5;
        time_now = HAL_GetTick();
      }

      break;
    case 4:
      Play_Tetris(screen, button_mask);
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
    Charlieplex_Display(matrix_ports, NUM_MATRIX_PORTS, matrix_pins, NUM_MATRIX_PINS, screen, 14);
  }
}

/**
 * @brief Polls buttons and returns a bitmask of newly pressed buttons.
 *
 * Detects edge-triggered presses for up to 16 buttons. Returns a bitmask where bit i is set
 * if button i was just pressed (transitioned to PressState).
 *
 * @param ButtonPorts Array of GPIO port pointers.
 * @param NumPorts Number of GPIO ports (must equal NumPins, max 16).
 * @param ButtonPins Array of GPIO pin numbers.
 * @param NumPins Number of pins (must equal NumPorts, max 16).
 * @param PressState GPIO state considered as "pressed" (e.g. GPIO_PIN_RESET).
 *
 * @retval 16-bit bitmask of newly pressed buttons, or 0 on input error.
 */
uint8_t Poll_Buttons(GPIO_TypeDef **ButtonPorts, int NumPorts, uint16_t *ButtonPins, int NumPins, uint8_t PressState)
{
  if (NumPorts != NumPins || NumPorts > 8 || NumPins > 8)
  {
    return 0;
  }

  uint8_t return_val = 0;
  static uint8_t button_flags[8] = {0, 0, 0, 0, 0, 0, 0, 0};
  for (int i = 0; i < NumPins; i++)
  {
    if (HAL_GPIO_ReadPin(ButtonPorts[i], ButtonPins[i]) == PressState && button_flags[i] == 0)
    {
      button_flags[i] = 1;
      return_val |= (1 << i);
    }
    else if (HAL_GPIO_ReadPin(ButtonPorts[i], ButtonPins[i]) == !PressState && button_flags[i] == 1)
    {
      button_flags[i] = 0;
    }
  }
  return return_val;
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
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_PLL;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
 * @brief TIM1 Initialization Function
 * @param None
 * @retval None
 */
static void MX_TIM1_Init(void)
{
  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  htim1.Instance = TIM1;
  htim1.Init.Prescaler = (HAL_RCC_GetPCLK2Freq() / 1000000) - 1;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 65535;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
 * @brief TIM2 Initialization Function
 * @param None
 * @retval None
 */
static void MX_TIM2_Init(void)
{
  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 0;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 65535; // max 16-bit
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
 * @brief USB Initialization Function
 * @param None
 * @retval None
 */
static void MX_USB_PCD_Init(void)
{

  /* USER CODE BEGIN USB_Init 0 */

  /* USER CODE END USB_Init 0 */

  /* USER CODE BEGIN USB_Init 1 */

  /* USER CODE END USB_Init 1 */
  hpcd_USB_FS.Instance = USB;
  hpcd_USB_FS.Init.dev_endpoints = 8;
  hpcd_USB_FS.Init.speed = PCD_SPEED_FULL;
  hpcd_USB_FS.Init.low_power_enable = DISABLE;
  hpcd_USB_FS.Init.lpm_enable = DISABLE;
  hpcd_USB_FS.Init.battery_charging_enable = DISABLE;
  if (HAL_PCD_Init(&hpcd_USB_FS) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USB_Init 2 */

  /* USER CODE END USB_Init 2 */
}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  for (int i = 0; i < (int)NUM_MATRIX_PINS; i++)
  {
    GPIO_InitStruct.Pin = matrix_pins[i];
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(matrix_ports[i], &GPIO_InitStruct);
  }

  for (int i = 0; i < (int)NUM_BUTTON_PINS; i++)
  {
    GPIO_InitStruct.Pin = button_pins[i];
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(button_ports[i], &GPIO_InitStruct);
  }

  GPIO_InitStruct.Pin = usb_enum_pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(usb_enum_pin_port, &GPIO_InitStruct);
}

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void)
{
  __disable_irq();
  while (1)
  {
  }
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