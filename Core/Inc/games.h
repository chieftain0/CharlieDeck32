#ifndef GAMES_H
#define GAMES_H

#include <stdint.h>

#define SCREEN_WIDTH 16
#define SCREEN_HEIGHT 15

void clear_screen(uint8_t matrix[SCREEN_HEIGHT][SCREEN_WIDTH]);
int Play_Snake(uint8_t matrix[SCREEN_HEIGHT][SCREEN_WIDTH], uint8_t button_mask, uint16_t random_number1, uint16_t random_number2, uint32_t time_now);
int Play_Pong(uint8_t matrix[SCREEN_HEIGHT][SCREEN_WIDTH], uint8_t button_mask);
int Play_FlappyBird(uint8_t matrix[SCREEN_HEIGHT][SCREEN_WIDTH], uint8_t button_mask, uint16_t random_number, uint32_t time_now);
int Play_Tetris(uint8_t matrix[SCREEN_HEIGHT][SCREEN_WIDTH], uint8_t button_mask);
void MainMenuMatrix(uint8_t matrix[SCREEN_HEIGHT][SCREEN_WIDTH]);
void ScoreMatrix(uint8_t matrix[SCREEN_HEIGHT][SCREEN_WIDTH], uint16_t score);
#endif