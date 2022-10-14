/*
 * Keypad.h
 *
 */
 
#ifndef INC_KEYPAD_H_
#define INC_KEYPAD_H_

#include "main.h"
#include "stdbool.h"
#include "pressed.h"

//Enum info for reference pressed{player1_up, player1_down, player2_up, player2_down, empty}

typedef struct Keypad_struct
{
		void (*update) (struct Keypad_struct *self);
		enum pressed (*get) (const struct Keypad_struct *self);
		enum pressed button_press;
}Keypad;

void keypad_init(Keypad *self);
void keypad_update(Keypad *self);
enum pressed Keypad_get(const Keypad *self);


#endif /* INC_KEYPAD_H_ */
