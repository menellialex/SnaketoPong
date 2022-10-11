/*
 * Keypad.h
 *
 */
 
#ifndef INC_KEYPAD_H_
#define INC_KEYPAD_H_

#include "main.h"
#include "stdbool.h"
#include "pressed.h"

//Enum pressed{player1_up, player1_down, player2_up, player2_down}

typedef struct Keypad_struct
{
		void (*update) (struct Keypad_struct *self);
		enum Pressed (*get) (const struct Keypad_struct *self);
		enum pressed button_press;
}Keypad;

void keypad_init(Keypad *self);
void keypad_update(Keypad *self);
enum pressed Keypad_get(const Keypad *self);

uint8_t scan_column(uint16_t pin_var);

#endif /* INC_KEYPAD_H_ */
