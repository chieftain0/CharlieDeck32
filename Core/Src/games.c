#include "games.h"

#include <stdlib.h>

#define Y 0
#define X 1

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

// Pong defines
#define PONG_SPEED 100

// Flappy Bird defines
#define FLAPPY_SPEED 200
#define GAP_SIZE 5
#define GRAVITY (-2)
#define JUMP 3

// Tetris defines

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
int Play_Snake(uint8_t matrix[SCREEN_HEIGHT][SCREEN_WIDTH], uint8_t button_mask_click, uint32_t time_now)
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
        for (int i = 0; i < SCREEN_HEIGHT * SCREEN_WIDTH; i++)
        {
            snakeLYX[i][Y] = -1;
            snakeLYX[i][X] = -1;
        }
        // Set the first 2 LYX in the middle facing down
        snakeLYX[0][0] = 6;
        snakeLYX[0][1] = 7;
        snakeLYX[1][0] = 5;
        snakeLYX[1][1] = 7;

        first_time_running = 0;
    }

    // If a button is pressed, change the directionYX if it is not forbidden
    if ((button_mask_click & 1) || (button_mask_click & 16)) // UP
    {
        if (directionYX[Y] != 1)
        {
            directionYX[Y] = -1;
            directionYX[X] = 0;
        }
    }
    else if ((button_mask_click & 8) || (button_mask_click & 128)) // RIGHT
    {
        if (directionYX[X] != -1)
        {
            directionYX[Y] = 0;
            directionYX[X] = 1;
        }
    }
    else if ((button_mask_click & 2) || (button_mask_click & 32)) // DOWN
    {
        if (directionYX[Y] != -1)
        {
            directionYX[Y] = 1;
            directionYX[X] = 0;
        }
    }
    else if ((button_mask_click & 4) || (button_mask_click & 64)) // LEFT
    {
        if (directionYX[X] != 1)
        {
            directionYX[Y] = 0;
            directionYX[X] = -1;
        }
    }

    if (spawn_food == 1)
    {
        uint8_t exit_flag = 0;
        while (exit_flag == 0)
        {
            exit_flag = 1;
            foodYX[Y] = rand() % 15;
            foodYX[X] = rand() % 16;

            for (int i = 0; i < length; i++)
            {
                if (snakeLYX[i][0] == foodYX[Y] && snakeLYX[i][1] == foodYX[X])
                {
                    exit_flag = 0;
                    break;
                }
            }
        }

        spawn_food = 0;
    }

    if (time_now - prev_time > SNAKE_SPEED)
    {
        prev_time = time_now;

        // Clear the screen
        clear_screen(matrix);

        // Move the snake's head
        prev_segmentYX[Y] = snakeLYX[Y][0];
        prev_segmentYX[X] = snakeLYX[Y][1];
        snakeLYX[Y][0] += directionYX[Y];
        snakeLYX[Y][1] += directionYX[X];

        // Wrap the snake's head
        snakeLYX[Y][0] = (snakeLYX[Y][0] + SCREEN_HEIGHT) % SCREEN_HEIGHT;
        snakeLYX[Y][1] = (snakeLYX[Y][1] + SCREEN_WIDTH) % SCREEN_WIDTH;

        // Check if snake eats itself
        for (int i = 1; i < length; i++)
        {
            if (snakeLYX[Y][0] == snakeLYX[i][0] && snakeLYX[Y][1] == snakeLYX[i][1])
            {
                return (length - 2);
            }
        }

        // Check if food is eaten
        if (snakeLYX[Y][0] == foodYX[Y] && snakeLYX[Y][1] == foodYX[X])
        {
            length++;
            spawn_food = 1;
        }

        // Move the snake's body
        for (int i = 1; i < length; i++)
        {
            uint8_t tempYX[2];
            tempYX[Y] = snakeLYX[i][0];
            tempYX[X] = snakeLYX[i][1];
            snakeLYX[i][0] = prev_segmentYX[Y];
            snakeLYX[i][1] = prev_segmentYX[X];
            prev_segmentYX[Y] = tempYX[Y];
            prev_segmentYX[X] = tempYX[X];
        }

        // Place the snake on the matrix
        for (int i = 0; i < length; i++)
        {
            matrix[snakeLYX[i][0]][snakeLYX[i][1]] = 1;
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
int Play_Pong(uint8_t matrix[SCREEN_HEIGHT][SCREEN_WIDTH], uint8_t button_mask_press, uint32_t time_now)
{
    static uint32_t prev_time = 0;

    static int8_t velocityYX[2] = {0, 0};
    static int8_t ballYX[2] = {SCREEN_HEIGHT / 2, SCREEN_WIDTH / 2};
    static int8_t playerLeftYX[2] = {SCREEN_HEIGHT / 2, 0};
    static int8_t playerRightYX[2] = {SCREEN_HEIGHT / 2, SCREEN_WIDTH - 1};

    uint8_t player_size = 3; // size of the player paddle (must be odd)

    static int score = 0;

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
        for (int i = 0; i < player_size / 2 + 1; i++)
        {
            if (ballYX[X] == playerLeftYX[X] && ballYX[Y] == (playerLeftYX[Y] + i))
            {
                velocityYX[X] = -velocityYX[X];
                velocityYX[Y] = i;
                score++;
                break;
            }
            if (ballYX[X] == playerLeftYX[X] && ballYX[Y] == (playerLeftYX[Y] - i))
            {
                velocityYX[X] = -velocityYX[X];
                velocityYX[Y] = -i;
                score++;
                break;
            }
            if (ballYX[X] == playerRightYX[X] && ballYX[Y] == (playerRightYX[Y] + i))
            {
                velocityYX[X] = -velocityYX[X];
                velocityYX[Y] = i;
                score++;
                break;
            }
            if (ballYX[X] == playerRightYX[X] && ballYX[Y] == (playerRightYX[Y] - i))
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
    for (int i = 0; i < player_size / 2 + 1; i++)
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
int Play_FlappyBird(uint8_t matrix[SCREEN_HEIGHT][SCREEN_WIDTH], uint8_t button_mask_click, uint32_t time_now)
{
    // If this is the first time running, clear the screen
    static uint8_t first_time_running = 1;
    if (first_time_running)
    {
        clear_screen(matrix);
        first_time_running = 0;
    }

    static uint32_t prev_time = 0;
    static int count = 0;
    static int score = -3;

    static int birdYX[2] = {7, 2};

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
            int random_height = rand() % (SCREEN_HEIGHT - GAP_SIZE - 1) + 1;
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

int Play_Tetris(uint8_t matrix[SCREEN_HEIGHT][SCREEN_WIDTH], uint8_t button_mask_click)
{
    if (button_mask_click)
    {
        for (int i = 0; i < SCREEN_HEIGHT; i++)
        {
            for (int j = 0; j < SCREEN_WIDTH; j++)
            {
                matrix[i][j] = heart_matrix[i][j];
            }
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