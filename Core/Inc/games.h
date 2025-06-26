#ifndef GAMES_H
#define GAMES_H

#include <stdbool.h>
#include <stdint.h>

void Play_Snake(int screen_width, int screen_height, bool matrix[screen_height - 1][screen_width], uint16_t button_mask);

#endif