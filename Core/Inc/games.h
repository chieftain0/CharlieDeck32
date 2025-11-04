#ifndef GAMES_H
#define GAMES_H

#include <stdint.h>

#define SCREEN_WIDTH 16
#define SCREEN_HEIGHT 15

void clear_screen(uint8_t matrix[SCREEN_HEIGHT][SCREEN_WIDTH]);
int32_t Play_Snake(uint8_t matrix[SCREEN_HEIGHT][SCREEN_WIDTH], uint8_t button_mask_click, uint32_t time_now);
int32_t Play_Pong(uint8_t matrix[SCREEN_HEIGHT][SCREEN_WIDTH], uint8_t button_mask_press, uint32_t time_now);
int32_t Play_FlappyBird(uint8_t matrix[SCREEN_HEIGHT][SCREEN_WIDTH], uint8_t button_mask_click, uint32_t time_now);
int32_t Play_Tetris(uint8_t matrix[SCREEN_HEIGHT][SCREEN_WIDTH], uint8_t button_mask_click, uint32_t time_now);
void MainMenuMatrix(uint8_t matrix[SCREEN_HEIGHT][SCREEN_WIDTH]);
void ScoreMatrix(uint8_t matrix[SCREEN_HEIGHT][SCREEN_WIDTH], uint16_t score);
#endif