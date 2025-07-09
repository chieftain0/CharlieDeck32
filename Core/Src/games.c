#include "games.h"

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

uint8_t menu_matrix[15][16] = {
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

uint8_t score_matrix[15][16] = {
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

uint8_t heart_matrix[15][16] = {
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

uint8_t smile_matrix[15][16] = {
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
    for (int i = 0; i < SCREEN_HEIGHT; i++)
    {
        for (int j = 0; j < SCREEN_WIDTH; j++)
        {
            matrix[i][j] = 0;
        }
    }
    return;
}

int Play_Snake(uint8_t matrix[SCREEN_HEIGHT][SCREEN_WIDTH], uint8_t button_mask, uint16_t random_number1, uint16_t random_number2, uint32_t time_now)
{
#define SPEED 200

    static unsigned long prev_time = 0;
    static int score = 0;

    static uint8_t direction = 1;           //  UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3
    static uint8_t forbidden_direction = 0; //  UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3
    static uint8_t foodYX[2] = {-1, -1};
    static uint8_t length = 3;
    static uint8_t snakeLYX[SCREEN_HEIGHT * SCREEN_WIDTH][2] = {{0, 0}};

    // If this is the first time running, clear the screen and prepare the snake
    static uint8_t first_time_running = 1;
    if (first_time_running)
    {
        clear_screen(matrix);

        // Set all snake LYX to -1
        for (int i = 0; i < SCREEN_HEIGHT * SCREEN_WIDTH; i++)
        {
            snakeLYX[i][0] = -1;
            snakeLYX[i][1] = -1;
        }
        // Set the first 3 LYX in the middle facing down
        snakeLYX[0][0] = 6;
        snakeLYX[0][1] = 7;
        snakeLYX[1][0] = 5;
        snakeLYX[1][1] = 7;
        snakeLYX[2][0] = 4;
        snakeLYX[2][1] = 7;

        first_time_running = 0;
    }

    // If a button is pressed, change the direction if it is not forbidden
    if ((button_mask & 1) || (button_mask & 16)) // UP
    {
        if (forbidden_direction != 0)
        {
            direction = 0;
            forbidden_direction = 1;
        }
    }
    else if ((button_mask & 8) || (button_mask & 128)) // RIGHT
    {
        if (forbidden_direction != 3)
        {
            direction = 3;
            forbidden_direction = 2;
        }
    }
    else if ((button_mask & 2) || (button_mask & 32)) // DOWN
    {
        if (forbidden_direction != 1)
        {
            direction = 1;
            forbidden_direction = 0;
        }
    }
    else if ((button_mask & 4) || (button_mask & 64)) // LEFT
    {
        if (forbidden_direction != 2)
        {
            direction = 2;
            forbidden_direction = 3;
        }
    }

    if (time_now - prev_time > SPEED)
    {
        prev_time = time_now;

        // Get the food YX (add checking)
        foodYX[0] = random_number1 % 15;
        foodYX[1] = random_number2 % 16;

        // Clear the screen
        clear_screen(matrix);
        // Move the snake
        for (int i = 0; i < length; i++)
        {
            if (direction == 0) // UP
            {
                snakeLYX[i][0]--;
            }
            else if (direction == 1) // DOWN
            {
                snakeLYX[i][0]++;
            }
            else if (direction == 2) // LEFT
            {
                snakeLYX[i][1]--;
            }
            else if (direction == 3) // RIGHT
            {
                snakeLYX[i][1]++;
            }
        }

        // Place the snake on the matrix
        for (int i = 0; i < length; i++)
        {
            matrix[snakeLYX[i][0]][snakeLYX[i][1]] = 1;
        }
    }

    return -1;
}

int Play_Pong(uint8_t matrix[SCREEN_HEIGHT][SCREEN_WIDTH], uint8_t button_mask)
{
    for (int i = 0; i < SCREEN_HEIGHT; i++)
    {
        for (int j = 0; j < SCREEN_WIDTH; j++)
        {
            matrix[i][j] = smile_matrix[i][j];
        }
    }
    return 0;
}

/**
 * @brief Flappy Bird game
 *
 * This function implements the game of Flappy Bird.
 *
 * @param matrix The screen matrix (15x16)
 * @param button_mask The mask of buttons pressed
 * @param random_number A random number to generate the next column of the game
 * @param time_now The current time
 *
 * @return -4 if the game is still running, otherwise the score
 */
int Play_FlappyBird(uint8_t matrix[SCREEN_HEIGHT][SCREEN_WIDTH], uint8_t button_mask, uint16_t random_number, uint32_t time_now)
{
#define SPEED 200
#define GAP_SIZE 5
#define GRAVITY (-2)
#define JUMP 3

    // If this is the first time running, clear the screen
    static uint8_t first_time_running = 1;
    if (first_time_running)
    {
        clear_screen(matrix);
        first_time_running = 0;
    }

    static unsigned long prev_time = 0;
    static int count = 0;
    static int score = -3;

    static int bird_yx[2] = {7, 2};

    static uint8_t jump_requested = 0;
    if (button_mask)
    {
        jump_requested = 1;
    }

    if (time_now - prev_time > SPEED)
    {
        prev_time = time_now;

        // Remove the bird for now
        matrix[bird_yx[0]][bird_yx[1]] = 0;

        // Shift the entire screen to the left
        for (int i = 0; i < SCREEN_HEIGHT; i++)
        {
            for (int j = 0; j < SCREEN_WIDTH - 1; j++)
            {
                matrix[i][j] = matrix[i][j + 1];
            }
        }
        for (int i = 0; i < SCREEN_HEIGHT; i++)
        {
            matrix[i][SCREEN_WIDTH - 1] = 0;
        }
        count++;

        if (count >= 5)
        {
            int random_height = random_number % (SCREEN_HEIGHT - GAP_SIZE - 1) + 1;
            for (int i = 0; i < random_height; i++)
            {
                matrix[SCREEN_HEIGHT - i - 1][SCREEN_WIDTH - 1] = 1;
            }
            for (int i = 0; i < SCREEN_HEIGHT - random_height - GAP_SIZE; i++)
            {
                matrix[i][SCREEN_WIDTH - 1] = 1;
            }
            count = 0;
            score++;
        }

        // Jump the bird if requested
        static double velocity = 0;
        if (jump_requested)
        {
            velocity = JUMP;
            jump_requested = 0;
        }
        else
        {
            velocity += GRAVITY;
        }

        bird_yx[0] -= velocity; // Subtract velocity since indexes are reversed
        if (bird_yx[0] > SCREEN_HEIGHT - 1)
        {
            bird_yx[0] = SCREEN_HEIGHT - 1;
        }
        if (bird_yx[0] < 0)
        {
            bird_yx[0] = 0;
        }

        if (matrix[bird_yx[0]][bird_yx[1]] == 1)
        {
            // Collision detected
            return score;
        }

        // Apply the bird
        matrix[bird_yx[0]][bird_yx[1]] = 1;
    }

    return -4;
}

int Play_Tetris(uint8_t matrix[SCREEN_HEIGHT][SCREEN_WIDTH], uint8_t button_mask)
{
    for (int i = 0; i < SCREEN_HEIGHT; i++)
    {
        for (int j = 0; j < SCREEN_WIDTH; j++)
        {
            matrix[i][j] = heart_matrix[i][j];
        }
    }
    return 0;
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
    for (int i = 0; i < SCREEN_HEIGHT; i++)
    {
        for (int j = 0; j < SCREEN_WIDTH; j++)
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
    for (int i = 0; i < SCREEN_HEIGHT; i++)
    {
        for (int j = 0; j < SCREEN_WIDTH; j++)
        {
            matrix[i][j] = score_matrix[i][j];
        }
    }

    uint8_t digits[4] = {(score / 1000) % 10, (score / 100) % 10, (score / 10) % 10, score % 10};
    for (int dig = 0; dig < 4; dig++)
    {
        for (int i = 9; i < 14; i++)
        {
            for (int j = dig * 4 + 1; j < dig * 4 + 4; j++)
            {
                matrix[i][j] = digit_matrices[digits[dig]][i - 9][j - (dig * 4 + 1)];
            }
        }
    }

    for (int i = (SCREEN_HEIGHT / 2) + 7; i < SCREEN_HEIGHT; i++)
    {
        for (int j = 0; j < SCREEN_WIDTH; j++)
        {
            matrix[i][j] = score_matrix[i][j];
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
    for (int i = 0; i < SCREEN_HEIGHT; i++)
    {
        for (int j = 0; j < SCREEN_WIDTH; j++)
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
    for (int i = 0; i < SCREEN_HEIGHT; i++)
    {
        for (int j = 0; j < SCREEN_WIDTH; j++)
        {
            matrix[i][j] = smile_matrix[i][j];
        }
    }
    return;
}