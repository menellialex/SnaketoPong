/*
 * Keypad.c
 *
 */
 
 #include <keypad.h>
 #include "main.h"
 #include "pressed.h"
 
 
// enum for reference  player1_up, player1_down, player2_up, player2_down, empty
 
uint4_t scan_column(uint16_t pin_var){ //function to determine which culumn is being obstructed / pressed
	uint4_t column;
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5|GPIO_PIN_6, GPIO_PIN_SET); //Set columns high
	
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET); //set column 1 high
	if (HAL_GPIO_WritePin(GPIOB, pin_var) == 0) //checks if sent row is low
		column = 1; //if it is sets int to 1
	
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET); //reset column 1 low
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET); //set column 2 high
	if (HAL_GPIO_WritePin(GPIOB, pin_var) == 0) //set column 2 high
		column = 2; //if it is sets int to 1
	
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5|GPIO_PIN_6, GPIO_PIN_SET); //Set both columns back low
	return column; //return column that was pressed
}


 
void keypad_init(Keypad *self) {
	 self->update = &Keypad_update;
	 self->get = &Keypad_get;
	 
	 self->button_press = EMPTY;
 }
 

 void Keypad_update(Keypad *self){
	 enum Pressed button_press = EMPTY;
	 uint4_t column_num;
	 
	 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1, GPIO_PIN_SET); //Set rows high
	 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5|GPIO_PIN_6, GPIO_PIN_RESET); //Set columns low
	 
	 if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0) == 0){
		 column_num = scan_column(GPIO_PIN_0); 
		 if (column_num == 1) //if top row and the left column is pressed
			 button_input = PLAYER1_UP;
		 if (column_num == 2) //if top row and right column is pressed
			 button_input = PLAYER1_DOWN;
	 }
	 else if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1) == 0){
		 column_num = scan_column(GPIO_PIN_0);
		 if (column_num == 1) //if bottom row and the left column is pressed
			 button_input = PLAYER2_UP;
		 if (column_num == 2) //if bottom row and right column is pressed
			 button_input = PLAYER2_DOWN;
	 }
	 else
		 input_player1 = EMPTY; //if no pins are set low there is no input and return empty
	 
	 self->button_press = button_input;
	 
 }
 
enum Press Keypad_get(const Keypad *self){
	 return self->button_press;
 }
