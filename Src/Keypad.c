/*
 * Keypad.c
 *
 */
 
 #include <keypad.h>
#include "main.h"
 
 
// enum for reference  player1_up, player1_down, player2_up, player2_down, empty
 



 
void keypad_init(Keypad *self) {
	 self->update = &keypad_update;
	 self->get = &Keypad_get;
	 self->button_press = EMPTY;
 }
 

 void keypad_update(Keypad *self)
 {
	 enum pressed button_input;
	 GPIOB->PUPDR |=(0x55); //PB0-3 pull up
	 GPIOB->MODER |=(1<<0); //PB0 output
	 GPIOB->ODR &=~(1<<0); //PB0 low
	 if ((GPIOB->IDR & (1<<2)) == 0){ //top left button is pressed
		 button_input = PLAYER1_UP;
	 }
	 if ((GPIOB->IDR & (1<<3))==0){ //bottom left button is pressed
		 button_input = PLAYER1_DOWN;
	 }

	 GPIOB->MODER &= ~(1<<0); //PB0 input
	 GPIOB->MODER |=(1<<2); //PB1 output
	 GPIOB->ODR &=~(1<<1); //PB1 low

	 if ((GPIOB->IDR & (1<<2))==0){ //top right button is pressed
	 	 button_input = PLAYER2_UP;
	 }
	 if ((GPIOB->IDR & (1<<3))==0){ //bottom right button is pressed
	 	 button_input = PLAYER2_DOWN;
	 }

	 GPIOB->MODER &= ~(1<<2); //PB1 input
	 
	 self->button_press = button_input;
	 
 }

enum pressed Keypad_get(const Keypad *self){
		return self->button_press;
}

