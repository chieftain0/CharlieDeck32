#include "games.h"

#include <stdlib.h>

#define Y 0
#define X 1

#ifndef SCREEN_WIDTH
#define SCREEN_WIDTH 16
#endif

#ifndef SCREEN_HEIGHT
#define SCREEN_HEIGHT 15
#endif

// Button defines from main.c (remap if needed)
#define BUTTON_UP (1 << 0)    // 0x01
#define BUTTON_DOWN (1 << 1)  // 0x02
#define BUTTON_LEFT (1 << 2)  // 0x04
#define BUTTON_RIGHT (1 << 3) // 0x08
#define BUTTON_C (1 << 4)     // 0x10
#define BUTTON_A (1 << 5)     // 0x20
#define BUTTON_D (1 << 6)     // 0x40
#define BUTTON_B (1 << 7)     // 0x80

// Snake defines
#define SNAKE_SPEED 200
#define HEAD 0

// Pong defines
#define PONG_SPEED 100

// Flappy Bird defines
#define FLAPPY_SPEED 200
#define GAP_SIZE 5
#define GRAVITY (-2)
#define JUMP 3

// Tetris defines
#define CLOCKWISE 0
#define COUNTERCLOCKWISE 1
#define TETRIS_SPEED 100
#define TETRIS_GRAVITY (-1)

// 0deg, 90deg, 180deg, 270deg
uint8_t I_tetromino[4][3][3] = {
    {
        {1, 0, 0},
        {1, 0, 0},
        {1, 0, 0},
    },
    {
        {1, 1, 1},
        {0, 0, 0},
        {0, 0, 0},
    },
    {
        {1, 0, 0},
        {1, 0, 0},
        {1, 0, 0},
    },
    {
        {1, 1, 1},
        {0, 0, 0},
        {0, 0, 0},
    },
};
uint8_t O_tetromino[4][3][3] = {
    {
        {1, 1, 0},
        {1, 1, 0},
        {0, 0, 0},
    },
    {
        {1, 1, 0},
        {1, 1, 0},
        {0, 0, 0},
    },
    {
        {1, 1, 0},
        {1, 1, 0},
        {0, 0, 0},
    },
    {
        {1, 1, 0},
        {1, 1, 0},
        {0, 0, 0},
    },
};
uint8_t T_tetromino[4][3][3] = {
    {
        {1, 1, 1},
        {0, 1, 0},
        {0, 0, 0},
    },
    {
        {1, 0, 0},
        {1, 1, 0},
        {1, 0, 0},
    },
    {
        {0, 1, 0},
        {1, 1, 1},
        {0, 0, 0},
    },
    {
        {0, 1, 0},
        {1, 1, 0},
        {0, 1, 0},
    },
};
uint8_t S_tetromino[4][3][3] = {
    {
        {0, 1, 1},
        {1, 1, 0},
        {0, 0, 0},
    },
    {
        {1, 0, 0},
        {1, 1, 0},
        {0, 1, 0},
    },
    {
        {0, 1, 1},
        {1, 1, 0},
        {0, 0, 0},
    },
    {
        {1, 0, 0},
        {1, 1, 0},
        {0, 1, 0},
    },
};
uint8_t Z_tetromino[4][3][3] = {
    {
        {1, 1, 0},
        {0, 1, 1},
        {0, 0, 0},
    },
    {
        {0, 1, 0},
        {1, 1, 0},
        {1, 0, 0},
    },
    {
        {1, 1, 0},
        {0, 1, 1},
        {0, 0, 0},
    },
    {
        {0, 1, 0},
        {1, 1, 0},
        {1, 0, 0},
    },
};
uint8_t L_tetromino[4][3][3] = {
    {
        {1, 0, 0},
        {1, 0, 0},
        {1, 1, 0},
    },
    {
        {0, 0, 1},
        {1, 1, 1},
        {0, 0, 0},
    },
    {
        {1, 1, 0},
        {0, 1, 0},
        {0, 1, 0},
    },
    {
        {1, 1, 1},
        {0, 0, 1},
        {0, 0, 0},
    },
};
uint8_t J_tetromino[4][3][3] = {
    {
        {0, 1, 0},
        {0, 1, 0},
        {1, 1, 0},
    },
    {
        {1, 1, 1},
        {0, 0, 1},
        {0, 0, 0},
    },
    {
        {1, 1, 0},
        {1, 0, 0},
        {1, 0, 0},
    },
    {
        {0, 0, 1},
        {1, 1, 1},
        {0, 0, 0},
    },
};

// Numbers
#define N0 {{1, 1, 1}, {1, 0, 1}, {1, 0, 1}, {1, 0, 1}, {1, 1, 1}}
#define N1 {{0, 0, 1}, {0, 0, 1}, {0, 0, 1}, {0, 0, 1}, {0, 0, 1}}
#define N2 {{1, 1, 1}, {0, 0, 1}, {1, 1, 1}, {1, 0, 0}, {1, 1, 1}}
#define N3 {{1, 1, 1}, {0, 0, 1}, {1, 1, 1}, {0, 0, 1}, {1, 1, 1}}
#define N4 {{1, 0, 1}, {1, 0, 1}, {1, 1, 1}, {0, 0, 1}, {0, 0, 1}}
#define N5 {{1, 1, 1}, {1, 0, 0}, {1, 1, 1}, {0, 0, 1}, {1, 1, 1}}
#define N6 {{1, 1, 1}, {1, 0, 0}, {1, 1, 1}, {1, 0, 1}, {1, 1, 1}}
#define N7 {{1, 1, 1}, {0, 0, 1}, {0, 0, 1}, {0, 0, 1}, {0, 0, 1}}
#define N8 {{1, 1, 1}, {1, 0, 1}, {1, 1, 1}, {1, 0, 1}, {1, 1, 1}}
#define N9 {{1, 1, 1}, {1, 0, 1}, {1, 1, 1}, {0, 0, 1}, {1, 1, 1}}

uint8_t digit_matrices[10][5][3] = {N0, N1, N2, N3, N4, N5, N6, N7, N8, N9};

uint8_t menu_matrix[SCREEN_HEIGHT][SCREEN_WIDTH] = {
    {1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1},
    {1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1},
    {1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1},
    {1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1},
    {0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0},
    {0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0},
    {1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1},
    {0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0},
    {0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0},
    {0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0},
    {1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1},
    {1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1},
    {1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1},
    {1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1}};

uint8_t score_matrix[SCREEN_HEIGHT][SCREEN_WIDTH] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0},
    {0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0},
    {0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0},
    {0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0},
    {0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1},
    {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
    {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
    {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
    {0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

uint8_t heart_matrix[SCREEN_HEIGHT][SCREEN_WIDTH] = {
    {0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0},
    {0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0},
    {0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
    {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
    {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0}};

uint8_t smile_matrix[SCREEN_HEIGHT][SCREEN_WIDTH] = {
    {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
    {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
    {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
    {0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0},
    {1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1},
    {1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1},
    {1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1},
    {1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
    {0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0},
    {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
    {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
    {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0}};

void clear_screen(uint8_t matrix[SCREEN_HEIGHT][SCREEN_WIDTH])
{
    for (uint32_t i = 0; i < SCREEN_HEIGHT; i++)
    {
        for (uint32_t j = 0; j < SCREEN_WIDTH; j++)
        {
            matrix[i][j] = 0;
        }
    }
    return;
}

/**
 * @brief Updates the given matrix with the heart pattern.
 *
 * This function copies the predefined heart pattern from 'heart_matrix'
 * into the given matrix. The matrix represents the LED screen, and this
 * function sets it to display a heart.
 *
 * @param matrix The screen matrix (15x16) to be updated with the heart pattern.
 */
void HeartMatrix(uint8_t matrix[SCREEN_HEIGHT][SCREEN_WIDTH])
{
    for (uint32_t i = 0; i < SCREEN_HEIGHT; i++)
    {
        for (uint32_t j = 0; j < SCREEN_WIDTH; j++)
        {
            matrix[i][j] = heart_matrix[i][j];
        }
    }
    return;
}

/**
 * @brief Updates the given matrix with the smile pattern.
 *
 * This function copies the predefined smile pattern from 'smile_matrix'
 * into the given matrix. The matrix represents the LED screen, and this
 * function sets it to display a smile.
 *
 * @param matrix The screen matrix (15x16) to be updated with the smile pattern.
 */
void SmileMatrix(uint8_t matrix[SCREEN_HEIGHT][SCREEN_WIDTH])
{
    for (uint32_t i = 0; i < SCREEN_HEIGHT; i++)
    {
        for (uint32_t j = 0; j < SCREEN_WIDTH; j++)
        {
            matrix[i][j] = smile_matrix[i][j];
        }
    }
    return;
}

/**
 * @brief Snake game
 *
 * This function implements the game of Snake.
 *
 * @param matrix The screen matrix (15x16)
 * @param button_mask_click The mask of clicked buttons
 * @param time_now The current time
 *
 * @return -1 if the game is still running, otherwise the score
 */
int32_t Play_Snake(uint8_t matrix[SCREEN_HEIGHT][SCREEN_WIDTH], uint8_t button_mask_click, uint32_t time_now)
{
    static uint32_t prev_time = 0;

    static uint8_t foodYX[2] = {-1, -1};
    static uint8_t spawn_food = 1;

    static int8_t snakeLYX[SCREEN_HEIGHT * SCREEN_WIDTH][2] = {{0, 0}};
    static int8_t directionYX[2] = {1, 0};
    static int8_t prev_segmentYX[2] = {0, 0};
    static uint8_t length = 2;

    // If this is the first time running, clear the screen and prepare the snake
    static uint8_t first_time_running = 1;
    if (first_time_running)
    {
        clear_screen(matrix);

        // Set all snake LYX to -1
        for (uint32_t i = 0; i < SCREEN_HEIGHT * SCREEN_WIDTH; i++)
        {
            snakeLYX[i][Y] = -1;
            snakeLYX[i][X] = -1;
        }
        // Set the first 2 LYX in the middle facing down
        snakeLYX[HEAD][Y] = 6;
        snakeLYX[HEAD][X] = 7;
        snakeLYX[HEAD + 1][Y] = 5;
        snakeLYX[HEAD + 1][X] = 7;

        first_time_running = 0;
    }

    // Spawn food if needed
    if (spawn_food == 1)
    {
        uint8_t foodY_temp = rand() % SCREEN_HEIGHT;
        uint8_t foodX_temp = rand() % SCREEN_WIDTH;
        for (uint32_t i = 0; i < length; i++)
        {
            if (snakeLYX[i][Y] == foodY_temp && snakeLYX[i][X] == foodX_temp)
            {
                return -1;
            }
        }

        foodYX[Y] = foodY_temp;
        foodYX[X] = foodX_temp;
        spawn_food = 0;
    }

    // If a button is pressed, change the directionYX if it is not forbidden
    if ((button_mask_click & BUTTON_UP) || (button_mask_click & BUTTON_C)) // UP
    {
        if (directionYX[Y] != 1)
        {
            directionYX[Y] = -1;
            directionYX[X] = 0;
        }
    }
    else if ((button_mask_click & BUTTON_RIGHT) || (button_mask_click & BUTTON_B)) // RIGHT
    {
        if (directionYX[X] != -1)
        {
            directionYX[Y] = 0;
            directionYX[X] = 1;
        }
    }
    else if ((button_mask_click & BUTTON_DOWN) || (button_mask_click & BUTTON_A)) // DOWN
    {
        if (directionYX[Y] != -1)
        {
            directionYX[Y] = 1;
            directionYX[X] = 0;
        }
    }
    else if ((button_mask_click & BUTTON_LEFT) || (button_mask_click & BUTTON_D)) // LEFT
    {
        if (directionYX[X] != 1)
        {
            directionYX[Y] = 0;
            directionYX[X] = -1;
        }
    }

    if (time_now - prev_time > SNAKE_SPEED)
    {
        prev_time = time_now;

        // Clear the screen
        clear_screen(matrix);

        // Move the snake's head
        prev_segmentYX[Y] = snakeLYX[HEAD][Y];
        prev_segmentYX[X] = snakeLYX[HEAD][X];
        snakeLYX[HEAD][Y] += directionYX[Y];
        snakeLYX[HEAD][X] += directionYX[X];

        // Wrap the snake's head
        snakeLYX[HEAD][Y] = (snakeLYX[HEAD][Y] + SCREEN_HEIGHT) % SCREEN_HEIGHT;
        snakeLYX[HEAD][X] = (snakeLYX[HEAD][X] + SCREEN_WIDTH) % SCREEN_WIDTH;

        // Check if snake eats itself
        for (uint32_t i = 1; i < length; i++)
        {
            if (snakeLYX[HEAD][Y] == snakeLYX[i][Y] && snakeLYX[HEAD][X] == snakeLYX[i][X])
            {
                return (length - 2);
            }
        }

        // Check if food is eaten
        if (snakeLYX[HEAD][Y] == foodYX[Y] && snakeLYX[HEAD][X] == foodYX[X])
        {
            length++;
            spawn_food = 1;
        }

        // Move the snake's body
        for (uint32_t i = 1; i < length; i++)
        {
            uint8_t tempYX[2];
            tempYX[Y] = snakeLYX[i][Y];
            tempYX[X] = snakeLYX[i][X];
            snakeLYX[i][Y] = prev_segmentYX[Y];
            snakeLYX[i][X] = prev_segmentYX[X];
            prev_segmentYX[Y] = tempYX[Y];
            prev_segmentYX[X] = tempYX[X];
        }

        // Place the snake on the matrix
        for (uint32_t i = 0; i < length; i++)
        {
            matrix[snakeLYX[i][Y]][snakeLYX[i][X]] = 1;
        }

        // Place the food on the matrix
        matrix[foodYX[Y]][foodYX[X]] = 1;
    }

    return -1;
}

/**
 * @brief Pong game
 *
 * This function implements the game of Pong. It takes a screen matrix (15x16) and the
 * mask of pressed buttons as input, and returns the score when the game is over.
 *
 * @param matrix The screen matrix (15x16)
 * @param button_mask_press The mask of pressed buttons
 * @param time_now The current time
 *
 * @return The score when the game is over, otherwise -1
 */
int32_t Play_Pong(uint8_t matrix[SCREEN_HEIGHT][SCREEN_WIDTH], uint8_t button_mask_press, uint32_t time_now)
{
    static uint32_t prev_time = 0;

    static int8_t velocityYX[2] = {0, 0};
    static int8_t ballYX[2] = {SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2};
    static int8_t playerLeftYX[2] = {SCREEN_HEIGHT / 2, 0};
    static int8_t playerRightYX[2] = {SCREEN_HEIGHT / 2, SCREEN_WIDTH - 1};

    uint8_t player_size = 3; // size of the player paddle (must be odd)

    static uint32_t score = 0;

    static uint8_t first_time_running = 1;
    if (first_time_running)
    {
        clear_screen(matrix);

        // set initial random velocity
        velocityYX[Y] = 0;
        velocityYX[X] = rand() % 3 - 1;
        while (velocityYX[X] == 0)
        {
            velocityYX[X] = rand() % 3 - 1;
        }

        first_time_running = 0;
    }

    if (time_now - prev_time > PONG_SPEED)
    {
        prev_time = time_now;

        // Clear the screen
        clear_screen(matrix);

        // Check for player collisions
        for (uint32_t i = 0; i < (uint32_t)(player_size / 2 + 1); i++)
        {
            if (ballYX[X] == playerLeftYX[X] && ballYX[Y] == (uint8_t)(playerLeftYX[Y] + i))
            {
                velocityYX[X] = -velocityYX[X];
                velocityYX[Y] = i;
                score++;
                break;
            }
            if (ballYX[X] == playerLeftYX[X] && ballYX[Y] == (uint8_t)(playerLeftYX[Y] - i))
            {
                velocityYX[X] = -velocityYX[X];
                velocityYX[Y] = -i;
                score++;
                break;
            }
            if (ballYX[X] == playerRightYX[X] && ballYX[Y] == (uint8_t)(playerRightYX[Y] + i))
            {
                velocityYX[X] = -velocityYX[X];
                velocityYX[Y] = i;
                score++;
                break;
            }
            if (ballYX[X] == playerRightYX[X] && ballYX[Y] == (uint8_t)(playerRightYX[Y] - i))
            {
                velocityYX[X] = -velocityYX[X];
                velocityYX[Y] = -i;
                score++;
                break;
            }
        }

        // Check for border collision (top and bottom)
        if (ballYX[Y] <= 0)
        {
            velocityYX[Y] = -velocityYX[Y];
        }
        if (ballYX[Y] >= SCREEN_HEIGHT - 1)
        {
            velocityYX[Y] = -velocityYX[Y];
        }

        // Move the ball
        ballYX[Y] += velocityYX[Y];
        ballYX[X] += velocityYX[X];

        // Move the players
        if ((button_mask_press & BUTTON_UP) && (playerLeftYX[Y] > (player_size / 2)))
        {
            playerLeftYX[Y] -= 1;
        }
        if ((button_mask_press & BUTTON_DOWN) && (playerLeftYX[Y] < SCREEN_HEIGHT - 1 - (player_size / 2)))
        {
            playerLeftYX[Y] += 1;
        }
        if ((button_mask_press & BUTTON_C) && (playerRightYX[Y] > (player_size / 2)))
        {
            playerRightYX[Y] -= 1;
        }
        if ((button_mask_press & BUTTON_A) && (playerRightYX[Y] < SCREEN_HEIGHT - 1 - (player_size / 2)))
        {
            playerRightYX[Y] += 1;
        }
    }

    // Check for out of bounds
    if ((ballYX[X] >= SCREEN_WIDTH) || (ballYX[X] < 0))
    {
        return score;
    }

    // Place the ball on the matrix
    matrix[ballYX[Y]][ballYX[X]] = 1;
    // Place the players on the matrix
    for (uint32_t i = 0; i < (uint32_t)(player_size / 2 + 1); i++)
    {
        matrix[playerLeftYX[Y] - i][playerLeftYX[X]] = 1;
        matrix[playerLeftYX[Y] + i][playerLeftYX[X]] = 1;
        matrix[playerRightYX[Y] - i][playerRightYX[X]] = 1;
        matrix[playerRightYX[Y] + i][playerRightYX[X]] = 1;
    }

    return -1;
}

/**
 * @brief Flappy Bird game
 *
 * This function implements the game of Flappy Bird.
 *
 * @param matrix The screen matrix (15x16)
 * @param button_mask_click The mask of clicked buttons
 * @param random_number A random number to generate the next column of the game
 * @param time_now The current time
 *
 * @return -4 if the game is still running, otherwise the score
 */
int32_t Play_FlappyBird(uint8_t matrix[SCREEN_HEIGHT][SCREEN_WIDTH], uint8_t button_mask_click, uint32_t time_now)
{
    // If this is the first time running, clear the screen
    static uint8_t first_time_running = 1;
    if (first_time_running)
    {
        clear_screen(matrix);
        first_time_running = 0;
    }

    static uint32_t prev_time = 0;
    static uint32_t count = 0;
    static int32_t score = -3;

    static int32_t birdYX[2] = {7, 2};

    static uint8_t jump_requested = 0;
    if (button_mask_click)
    {
        jump_requested = 1;
    }

    if (time_now - prev_time > FLAPPY_SPEED)
    {
        prev_time = time_now;

        // Remove the bird for now
        matrix[birdYX[Y]][birdYX[X]] = 0;

        // Shift the entire screen to the left
        for (uint32_t i = 0; i < SCREEN_HEIGHT; i++)
        {
            for (uint32_t j = 0; j < SCREEN_WIDTH - 1; j++)
            {
                matrix[i][j] = matrix[i][j + 1];
            }
        }
        for (uint32_t i = 0; i < SCREEN_HEIGHT; i++)
        {
            matrix[i][SCREEN_WIDTH - 1] = 0;
        }
        count++;

        if (count >= 5)
        {
            uint32_t random_height = rand() % (SCREEN_HEIGHT - GAP_SIZE - 1) + 1;
            for (uint32_t i = 0; i < random_height; i++)
            {
                matrix[SCREEN_HEIGHT - i - 1][SCREEN_WIDTH - 1] = 1;
            }
            for (uint32_t i = 0; i < SCREEN_HEIGHT - random_height - GAP_SIZE; i++)
            {
                matrix[i][SCREEN_WIDTH - 1] = 1;
            }
            count = 0;
            score++;
        }

        // Jump the bird if requested
        static int32_t velocity = 0;
        if (jump_requested)
        {
            velocity = JUMP;
            jump_requested = 0;
        }
        else
        {
            velocity += GRAVITY;
        }

        birdYX[Y] -= velocity; // Subtract velocity since indexes are reversed
        if (birdYX[Y] > SCREEN_HEIGHT - 1)
        {
            birdYX[Y] = SCREEN_HEIGHT - 1;
        }
        if (birdYX[Y] < 0)
        {
            birdYX[Y] = 0;
        }

        if (matrix[birdYX[Y]][birdYX[X]] == 1)
        {
            // Collision detected
            return score;
        }

        // Apply the bird
        matrix[birdYX[Y]][birdYX[X]] = 1;
    }

    return -4;
}

int32_t Play_Tetris(uint8_t matrix[SCREEN_HEIGHT][SCREEN_WIDTH], uint8_t button_mask_click, uint32_t time_now)
{
    static uint32_t prev_time = 0;
    static uint8_t spawn_tetromino = 1;
    static uint8_t random_tetromino_index = 0;

    // If this is the first time running, clear the screen
    static uint8_t first_time_running = 1;
    if (first_time_running)
    {
        clear_screen(matrix);
        first_time_running = 0;
    }

    if (spawn_tetromino == 1)
    {
        random_tetromino_index = rand() % 7;
        spawn_tetromino = 0;
    }
}

/**
 * @brief Updates the given matrix with the main menu pattern.
 *
 * This function copies the predefined main menu pattern from 'menu_matrix'
 * into the given matrix. The matrix represents the LED screen, and this
 * function sets it to display the main menu.
 *
 * @param matrix The screen matrix (15x16) to be updated with the main menu pattern.
 */
void MainMenuMatrix(uint8_t matrix[SCREEN_HEIGHT][SCREEN_WIDTH])
{
    for (uint32_t i = 0; i < SCREEN_HEIGHT; i++)
    {
        for (uint32_t j = 0; j < SCREEN_WIDTH; j++)
        {
            matrix[i][j] = menu_matrix[i][j];
        }
    }
    return;
}

/**
 * @brief Updates the given matrix with the score pattern.
 *
 * This function copies the predefined score pattern from 'score_matrix'
 * into the given matrix. The matrix represents the LED screen, and this
 * function sets it to display the score.
 *
 * @param matrix The screen matrix (15x16) to be updated with the score pattern.
 * @param score  The score to be displayed.
 */
void ScoreMatrix(uint8_t matrix[SCREEN_HEIGHT][SCREEN_WIDTH], uint16_t score)
{
    for (uint32_t i = 0; i < SCREEN_HEIGHT; i++)
    {
        for (uint32_t j = 0; j < SCREEN_WIDTH; j++)
        {
            matrix[i][j] = score_matrix[i][j];
        }
    }

    uint8_t digits[4] = {(score / 1000) % 10, (score / 100) % 10, (score / 10) % 10, score % 10};
    for (uint32_t dig = 0; dig < 4; dig++)
    {
        for (uint32_t i = 9; i < 14; i++)
        {
            for (uint32_t j = dig * 4 + 1; j < dig * 4 + 4; j++)
            {
                matrix[i][j] = digit_matrices[digits[dig]][i - 9][j - (dig * 4 + 1)];
            }
        }
    }

    for (uint32_t i = (SCREEN_HEIGHT / 2) + 7; i < SCREEN_HEIGHT; i++)
    {
        for (uint32_t j = 0; j < SCREEN_WIDTH; j++)
        {
            matrix[i][j] = score_matrix[i][j];
        }
    }
    return;
}
