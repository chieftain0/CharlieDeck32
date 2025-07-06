#ifndef GAMES_H
#define GAMES_H

#include <stdint.h>

#define SCREEN_WIDTH 16
#define SCREEN_HEIGHT 15

void Play_Snake(uint8_t matrix[SCREEN_HEIGHT][SCREEN_WIDTH], uint16_t button_mask);
void Play_Pong(uint8_t matrix[SCREEN_HEIGHT][SCREEN_WIDTH], uint16_t button_mask);
int Play_FlappyBird(uint8_t matrix[SCREEN_HEIGHT][SCREEN_WIDTH], uint16_t button_mask, uint16_t random_number, uint32_t time_now);
void Play_Tetris(uint8_t matrix[SCREEN_HEIGHT][SCREEN_WIDTH], uint16_t button_mask);
void MainMenuMatrix(uint8_t matrix[SCREEN_HEIGHT][SCREEN_WIDTH]);
void ScoreMatrix(uint8_t matrix[SCREEN_HEIGHT][SCREEN_WIDTH], uint16_t score);
#endif