/*
 * snake_main.h
 *
 *  Created on: Jul 26, 2022
 *      Author: carrolls
 */

#ifndef INC_SNAKE_MAIN_H_
#define INC_SNAKE_MAIN_H_

#define CHECKS_WIDE (((uint16_t)8))
#define PIXELS_PER_CHECK (((uint16_t) 8))
#define BIG_DELAY_COUNT 1234567L
#define MEMORY_BARRIER_1 0x1111
#define MEMORY_BARRIER_2 0x2222
#define MEMORY_BARRIER_3 0x3333
#define MEMORY_BARRIER_4 0x4444
void snake_main(void);

//start pong definitions

//start pong functions
void pong_main(void);


#endif /* INC_SNAKE_MAIN_H_ */
