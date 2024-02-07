/*
 * main.c
 *
 *  Created on: Feb 7, 2024
 *      Author: moham
 */


#include "HAL/KEYPAD/Keypad_interface.h"
#include "MCAL/USART/USART_interface.h"



int main()
{
	Keypad_init();
	USART_Init();

	while(1)
	{
		uint8 Keypad_pressed = Keypad_GetPressedKey();
		if((Keypad_pressed >= 0) && (Keypad_pressed <=7))
			USART_SendBytePolling(Keypad_pressed);
	}


}

