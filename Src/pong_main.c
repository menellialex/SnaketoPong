// Snake game demo for STM Board Nucleo-G071RB
// carrolls@trine.edu
// Copyright 2022 Sean Carroll
// 2022.7.26
//
// SURPRISE - I had to add "#include <stddef.h>' into file sysmem.c to define
// symbol NULL. An oversight by STM? Nice that it seems to be allowed --
// CLEAN and autobuild did not overwrite my improvement.

// This demo project shows coding examples of:
// * Comments
// * JPL compliance
// * Encapsulated, asynchronous IPC (queues)
// * ANSI C
// * OOP
// * Task-decoupling
// * Separated timing and operation logic
//
// Code overview:
// "Control" (i.e. input) in this project is
// one quad-encoded knob that sends messages
// {CW/CCW/NO_TURN} to the "model" via queue.
// The Model (aka process logic) plays "snake" on an 8x8
// grid; the model uses a queue to send a message
// "ready" to the "view."
// The View (i.e. output layer) draws the snake and
// fruit onto a 64 x 128 pixel display using 8x8 squares.
//
// Disclaimer:
// Yes - it could be prettier, but this is a demo of
// coding practices, not gaming.
// NOTES ON INTERRUPTS
// * I selected timer TIM17 as a periodic timer interrupt (simple timer)
// * CubeMX will generate "static void MX_TIM17_Init(void)" in main.c
// * I wrote the handler - named
// >> "void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)"
// >> as "{timer_isr_count--;}"
// >> where "timer_isr_count" is a volatile int global that I defined.
// * I added the line "HAL_TIM_Base_Start_IT(&htim17);" right after the
// >> CubeMX code calling "MX_TIM17_Init();"
//
// >> >> DOCUMENTATION is tricky: How did I find the name for the ISR, which
// >> >> appears to be "HAL_TIM_PeriodElapsedCallback"? Did I make it up?
// >> >> TWO answers: (1) Find a set of example projects online, and look
// >> >> through them until you find one that uses the interrupt you want.
// >> >> Answer(2): the ISR name is fixed by the Hardware Abstraction Layer
// >> >> header files. To find the name for any interrupt, start
// >> >> by finding the file Core/Inc/stm32g0xx_hal_conf.h
// >> >> in the project -- it points to all the other include files that our
// >> >> chip needs. There is one include file for each peripheral type,
// >> >> including the generic timer. Then find the name for the file that
// >> >> holds timer ISR names. Depending on how you like the IDE, there
// >> >> are 2 seek methods...
// >> >>
// >> >> File-seeking method #2A: You can use the CubeIDE to expand
// >> >> [> stm32g0xx_hal_conf.h] by clicking on the [ > ]. You'll see about
// >> >> 30 files, and stm32g0xx_hal_tim.h is one of them. Double-click it to
// >> >> find the line of stm32g0xx_hal_conf.h that #includes it.
// >> >>
// >> >> File-seeking method 2B: Slower, but does not depend on CubeIDE to
// >> >> extract file names. Open the file stm32g0xx_hal_conf.h. Near the
// >> >> bottom of that file, you'll find an "#ifdef HAL_TIM_MODULE_ENABLED"
// >> >> which is should be true if we intend to use any timers. This is the
// >> >> same line that you'd find using file-seeking method 2A.
// >> >> ONCE YOU FIND THE FILENAME "stm32g0xx_hal_tim.h"
// >> >> Once the file. Search for the word "callback" because that is what
// >> >> the HAL calls developer-written ISRs. My advice - Search backwards
// >> >> from the bottom of the file - usually constants are defined first,
// >> >> and function names at the end. In the version of the file from year
// >> >> 2022, the callback names for timers start at line # 2380, and the 1st
// >> >> one is void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
// >> >>
// >> >> THAT'S WHAT I WANT! "Call this every time the period elapses"
// >> >> sounds very promising. When I tried to out, it works as expected,
// >> >> after I debugged it: the configuration given does not START the
// >> >> timer. Add in the line "HAL_TIM_Base_Start_IT(&htim17);" right at the top
// >> >> of the User Code Part 2 in main.c.


#include <stdint.h>
#include <stdlib.h> // rand
#include <stdbool.h>
#include <cmsis_gcc.h>
#include <keypad.h>
#include "main.h"
#include "pong_main.h"
#include "pong_gameplay.h"
#include "display_DOGS_102.h"
#include "pong_enums.h"
#include "quadknob.h"
#include "smc_queue.h"
#include "show_pong.h"
#include "circle_queue.h"

///////////////////////////
// Test -without input, the expected output = snake goes straight ahead every 1/2 second.
// Without_Input - Works!
//#define TEST_WITHOUT_INPUT

#define PONG_TEST

// Test - with input: ... (a) Slithering is OK!
// (b) Turning works - 1 or several detents turn correctly, reliably.
// (c) New fruit is visible.
// (d) The tail of the snake follows the head correctly.
// (e) the display sometimes flips to 12-o'clock position instead of
// 6 o'clock? SUSPICIOUS - wiring/ground at the knob... when I am gentle
// this does not happen. ACCEPTABLE.

extern volatile int32_t timer_isr_countdown; // Required to control timing
const int snake_board_size = CHECKS_WIDE; // Provided for extern

void ram_health(uint16_t dummy_var, uint16_t pattern){
	// DEBUGGING PHASE: LOCK UP THE PROGRAM if RAM is corrupted.
	if (dummy_var != pattern){
		while(1);
	}
}


void pong_main(void){
	const int32_t timer_isr_500ms_restart = 500;
	const int32_t timer_isr_2000ms_restart = 2000;

	circle_queue queue;
	volatile uint16_t ram_dummy_2 = MEMORY_BARRIER_2;
	circle_queue_init(&queue);

	// keypad init
	struct Keypad_struct keypad_obj;
	volatile uint16_t ram_dummy_3 = MEMORY_BARRIER_3;
	keypad_init(&keypad_obj);

	//pong game init
	pong_game pong_game;
	volatile uint16_t ram_dummy_4 = MEMORY_BARRIER_4;
	pong_init(&pong_game);

	// Output object
	// Block all interrupts while initializing - initial protocol timing is critical.
	__disable_irq();
	display_init();
	__enable_irq();

	// Welcome screen = checkerboard for 2 seconds.
	timer_isr_countdown = timer_isr_2000ms_restart;
	display_checkerboard();
	while (timer_isr_countdown > 0){}
	timer_isr_countdown = timer_isr_500ms_restart;
	// Confirm all the rules and paint the initial snake.
	display_blank();
	//snake_game_cleanup(&my_game);

	//display the game
	update_pong_display(&pong_game, true);

	// OPERATE THE GAME
	int32_t prior_timer_countdown = timer_isr_countdown;


	while(1){
		//ram_health(ram_dummy_1, MEMORY_BARRIER_1); dont need
		ram_health(ram_dummy_2, MEMORY_BARRIER_2);
		ram_health(ram_dummy_3, MEMORY_BARRIER_3);
		ram_health(ram_dummy_4, MEMORY_BARRIER_4);

	// ASSERT TIMER COUNTDOWN IN RANGE
		if ((timer_isr_countdown > timer_isr_500ms_restart)||
				(timer_isr_countdown < 0)){
			display_checkerboard();
			while(1);
		}

#ifdef PONG_TEST

		// checks every 1 ms for a input
		if (prior_timer_countdown != timer_isr_countdown )
		{
			//resets counter
			prior_timer_countdown = timer_isr_countdown;


			GPIOB->PUPDR |= (0x55);// PB0-3 pullup
			GPIOB->MODER |= (0x5); // PB0 and PB1 output
			GPIOB->ODR &= ~(0x3); // PB 0 and PB1 low
			if((GPIOB->IDR & (1<<2)) ==0) //check if any button is pressed
			{
				//reset Mode
				GPIOB->MODER &= ~(0x5);
				keypad_update(&keypad_obj); //call function

				if (keypad_obj.button_press != EMPTY && keypad_obj.button_press != PLAYER1_UP &&
						keypad_obj.button_press != PLAYER2_DOWN && keypad_obj.button_press != PLAYER2_UP &&
						keypad_obj.button_press != PLAYER1_DOWN)
				{
					while(1);
				}

				//store in queue
				enum pressed message = keypad_obj.button_press;
				//checks if the queue.put went well, if not freeze
				if (queue.put(&queue,&message) != true)
				{
						while(1);
				}
			}
			if((GPIOB->IDR & (1<<3)) ==0) //check if any button is pressed
			{
				//reset Mode
				GPIOB->MODER &= ~(0x5);
				keypad_update(&keypad_obj); //call function

				//store in queue
				enum pressed message = keypad_obj.button_press;

				//assert keypad button press
				if (keypad_obj.button_press != EMPTY && keypad_obj.button_press != PLAYER1_UP &&
						keypad_obj.button_press != PLAYER2_DOWN && keypad_obj.button_press != PLAYER2_UP &&
						keypad_obj.button_press != PLAYER1_DOWN)
				{
					while(1);
				}

				if (queue.put(&queue,&message) != true)
				{
						while(1);
				}
			}

			//assert that the direction of the left bar is okay
			if (pong_game.left_direction != NONE && pong_game.left_direction != UP && pong_game.left_direction != DOWN)
			{
				//freeze
				while(1);
			}

			bars_heading_update(&pong_game, &queue);
		}

		//animate every 500 ms
		if (timer_isr_countdown <= 0)
		{
			//restart timer
			timer_isr_countdown = timer_isr_500ms_restart;

			//assert that the direction of right bar is okay
			if (pong_game.right_direction != NONE && pong_game.right_direction != UP && pong_game.right_direction != DOWN)
			{
				//freeze
				while(1);
			}


			//move ball and bar one frame
			pong_periodic_play(&pong_game);

			//paint on screen
			update_pong_display(&pong_game, true);

			//makes pad not move maybe?
			keypad_obj.button_press = EMPTY;


			//checks if either side won
			if (pong_game.ball_position.x < 0 || pong_game.ball_position.x > 8)
			{
				display_checkerboard();
				while(1)
				{
					//freeze
				}
			}
		}

#endif PONG_TEST

//Dr. Carrols code for the loop
/*
#ifndef TEST_WITHOUT_INPUT
		// Check for user input every 1 ms & paint one block of the display.
		if (prior_timer_countdown != timer_isr_countdown ){
			prior_timer_countdown = timer_isr_countdown;
			// If time changed, about 1 ms has elapsed.
			// Once each 1 ms, read input pins from user knob and then
			// update "knob" object (which debounces each input pin and
			// then calculates user command).

			bool user_knob_1_pin_A = (GPIO_PIN_SET == HAL_GPIO_ReadPin(QuadKnobA_GPIO_Port, QuadKnobA_Pin));
			bool user_knob_1_pin_B = (GPIO_PIN_SET == HAL_GPIO_ReadPin(QuadKnobB_GPIO_Port, QuadKnobB_Pin));
			user_knob_1.update(&user_knob_1, user_knob_1_pin_A, user_knob_1_pin_B);

			// Get user command from "knob" - if any action, make it a queue packet and then mail it.
			if (user_knob_1.get(&user_knob_1) != QUADKNOB_STILL){
				Q_data command_packet;
				command_packet.twist = user_knob_1.get(&user_knob_1);
				turn_q.put(&turn_q, &command_packet);
			}
			snake_heading_update(&my_game, &turn_q);
		// ASSERT HEADING IS VALID
			while ((my_game.heading != SNAKE_COMPASS_N)&&
					(my_game.heading != SNAKE_COMPASS_E)&&
					(my_game.heading != SNAKE_COMPASS_S)&&
					(my_game.heading != SNAKE_COMPASS_W));
			incremental_show_snake((const snake_game *)&my_game, false);
		}
		if (timer_isr_countdown <= 0) {
			// Move and animate every 500 ms
			timer_isr_countdown = timer_isr_500ms_restart;
			//moves the snake one increment
			snake_periodic_play(&my_game);
			//shows the snake on the board
			incremental_show_snake(&my_game, true);
		}
#endif
*/
#ifdef TEST_WITHOUT_INPUT
		static int turns = 0;
		// Normally "check for user input every 1 ms & show" - here just update display
		if (prior_timer_countdown != timer_isr_countdown ){
			prior_timer_countdown = timer_isr_countdown;
			incremental_show_snake(&my_game, false);
		}
		if (timer_isr_countdown <= 0) {
			// Move and animate every 500 ms
			timer_isr_countdown = timer_isr_500ms_restart;
			if (turns < 3){
				turns ++;
				snake_periodic_play(&my_game);
			}
			else {
				turns = 0;
				Q_data command_packet = {.twist = QUADKNOB_CW};
				turn_q.put(&turn_q, &command_packet);
				snake_heading_update(&my_game, &turn_q);
				snake_periodic_play(&my_game);
			}
			incremental_show_snake(&my_game, true);
		}
#endif
	}
}

// Time-wasting counter as delay (about 2 seconds).
// for (uint32_t i = 0; i < 2345678; i++){;} // pause several sec b4 repeat all
