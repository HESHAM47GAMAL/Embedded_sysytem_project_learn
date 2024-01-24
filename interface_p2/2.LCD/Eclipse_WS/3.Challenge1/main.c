/*
 * main.c
 *
 *  Created on: Jan 24, 2024
 *      Author: moham
 */


#include "MCAL/GPIO/GPIO_interface.h"
#include "HAL/LCD/LCD_interface.h"
#include "HAL/KEYPAD/Keypad_interface.h"

#include <util/delay.h>

int main (void)
{
	LCD_init();
	Keypad_init();
	LCD_DisplayStringRowCol("Challenge",0,0);
	_delay_ms(3000);
	LCD_DisplayStringRowCol("Keypad 4*4",1,0);
	_delay_ms(5000);
	LCD_ClearScreen();


	while(1)
	{
		uint8 keypad_pressed_Button = Keypad_GetPressedKey();
		if(keypad_pressed_Button>=0 && keypad_pressed_Button <= 9)
		{
			LCD_intToString(LCD_intToString);
		}
		else
		{
			LCD_DisplayCharacter( keypad_pressed_Button);
		}
	}

}
