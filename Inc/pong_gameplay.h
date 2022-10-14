/*
 * snake_gameplay.h
 *
 *  Created on: Jul 28, 2022
 *      Author: carrolls
 */

#ifndef SNAKE_GAMEPLAY_H_
#define SNAKE_GAMEPLAY_H_

#include <stdint.h>
#include <stdbool.h>
#include "quadknob.h"
#include "pong_enums.h"
#include "smc_queue.h"
#include "pong_main.h" // Get checks and display width
#include "circle_queue.h"

typedef struct {int16_t x; int16_t y;} XY_PT;

typedef struct {
	enum snake_compass_dir vertebra[CHECKS_WIDE * CHECKS_WIDE];
	XY_PT head;
	XY_PT fruit;
	uint8_t length;
	enum snake_compass_dir heading;
} snake_game;

enum snake_compass_dir snake_opposite_direction(enum snake_compass_dir d);
void snake_game_init(snake_game* s);
void snake_game_cleanup(snake_game* s);
void snake_heading_update(snake_game* snake, Smc_queue* q);
void snake_periodic_play(snake_game *snake);
void snake_place_fruit(snake_game * s, const int8_t b[CHECKS_WIDE][CHECKS_WIDE]);
bool snake_plot(const snake_game *s, int8_t b[CHECKS_WIDE][CHECKS_WIDE]);
bool fruit_plot(const snake_game *s, int8_t b[CHECKS_WIDE][CHECKS_WIDE]);


// start pong variables
typedef struct
{
	XY_PT left_top;
	XY_PT left_middle;
	XY_PT left_bottom;
	enum bar_direction left_direction;

	XY_PT right_top;
	XY_PT right_middle;
	XY_PT right_bottom;
	enum bar_direction right_direction;

	XY_PT ball_position;
	enum ball_direction ball_direction;
	bool ball_reverse;
} pong_game;

//start pong gameplay functions
void pong_init(pong_game* pg);
void pong_plot(pong_game* pg, int8_t b[CHECKS_WIDE][CHECKS_WIDE]);
void ball_plot(pong_game* pg, int8_t b[CHECKS_WIDE][CHECKS_WIDE]);
void pong_periodic_play(pong_game*);
void ball_state(pong_game* pg);
void check_ball_collision(pong_game* pg);
void bars_heading_update(pong_game* pg, circle_queue* q);

#endif /* SNAKE_GAMEPLAY_H_ */

