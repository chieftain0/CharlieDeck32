#ifndef GAMES_H
#define GAMES_H

#include <stdbool.h>
#include <stdint.h>

void Play_Snake(int screen_width, int screen_height, bool matrix[screen_height][screen_width], uint16_t button_mask);
void Play_Pong(int screen_width, int screen_height, bool matrix[screen_height][screen_width], uint16_t button_mask);
int Play_FlappyBird(int screen_width, int screen_height, bool matrix[screen_height][screen_width], uint16_t button_mask, uint16_t random_number, uint16_t speed_ms);

#endif