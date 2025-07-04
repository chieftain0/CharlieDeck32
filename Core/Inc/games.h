#ifndef GAMES_H
#define GAMES_H

#include <stdint.h>

void Play_Snake(int screen_width, int screen_height, uint8_t matrix[screen_height][screen_width], uint16_t button_mask);
void Play_Pong(int screen_width, int screen_height, uint8_t matrix[screen_height][screen_width], uint16_t button_mask);
int Play_FlappyBird(int screen_width, int screen_height, uint8_t matrix[screen_height][screen_width], uint16_t button_mask, uint16_t random_number, uint32_t time_now);
void Play_Tetris(int screen_width, int screen_height, uint8_t matrix[screen_height][screen_width], uint16_t button_mask);
#endif