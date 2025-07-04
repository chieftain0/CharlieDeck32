#include "games.h"

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

/**
 * @brief Plays the snake game (WORK IN PROGRESS, OUTPUTS A HEART)
 * @param[in] screen_width Screen width
 * @param[in] screen_height Screen height
 * @param[out] matrix 2D array of uint8_ts representing the screen
 * @param[in] button_mask Button mask, unused in this function
 */
void Play_Snake(int screen_width, int screen_height, uint8_t matrix[screen_height][screen_width], uint16_t button_mask)
{
    for (int i = 0; i < screen_height; i++)
    {
        for (int j = 0; j < screen_width; j++)
        {
            matrix[i][j] = heart_matrix[i][j];
        }
    }
}

/**
 * @brief Plays the ping pong game (WORK IN PROGRESS, OUTPUTS A SMILE)
 * @param[in] screen_width Screen width
 * @param[in] screen_height Screen height
 * @param[out] matrix 2D array of uint8_ts representing the screen
 * @param[in] button_mask Button mask, unused in this function
 */
void Play_Pong(int screen_width, int screen_height, uint8_t matrix[screen_height][screen_width], uint16_t button_mask)
{
    for (int i = 0; i < screen_height; i++)
    {
        for (int j = 0; j < screen_width; j++)
        {
            matrix[i][j] = smile_matrix[i][j];
        }
    }
}

int Play_FlappyBird(int screen_width, int screen_height, uint8_t matrix[screen_height][screen_width], uint16_t button_mask, uint16_t random_number, uint32_t time_now)
{
#define SPEED 200
#define GRAVITY 0.5
#define JUMP 1
    static unsigned long prev_time = 0;
    static int count = 0;
    static int score = -2;

    static int bird_yx[2] = {7, 2};

    if (time_now - prev_time > SPEED)
    {
        prev_time = time_now;

        // Remove the bird for now
        matrix[bird_yx[0]][bird_yx[1]] = 0;

        // Shift the entire screen to the left
        for (int i = 0; i < screen_height; i++)
        {
            for (int j = 0; j < screen_width - 1; j++)
            {
                matrix[i][j] = matrix[i][j + 1];
            }
        }
        for (int i = 0; i < screen_height; i++)
        {
            matrix[i][screen_width - 1] = 0;
        }
        count++;

        if (count >= 5)
        {
            // Make a new column
            int random_height = random_number % 11 + 1;
            for (int i = 0; i < random_height; i++)
            {
                matrix[screen_height - i - 1][screen_width - 1] = 1;
            }
            for (int i = 0; i < screen_height - random_height - 3; i++)
            {
                matrix[i][screen_width - 1] = 1;
            }
            count = 0;
            score++;
        }

        // Jump the bird
        static double velocity = 0;
        if (bird_yx[0] > 0) // If the bird is not on the ground
        {
            velocity -= GRAVITY;
        }
        else
        {
            velocity = 0;
        }
        if ((button_mask & 0x80) || (button_mask & 0x8)) // If the button is pressed
        {
            velocity += JUMP;
        }
        bird_yx[0] -= velocity; // Subtract velocity since indexes are reversed
        if (bird_yx[0] > screen_height - 1)
        {
            bird_yx[0] = screen_height - 1;
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

    return -1;
}

void Play_Tetris(int screen_width, int screen_height, uint8_t matrix[screen_height][screen_width], uint16_t button_mask)
{
}