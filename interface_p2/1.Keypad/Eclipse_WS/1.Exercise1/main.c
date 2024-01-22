/*
 * main.c
 *
 *  Created on: Jan 22, 2024
 *      Author: moham
 */

/**************************                   INCLUDES                   **************************/
#include "MCAL/GPIO/GPIO_interface.h"
#include "HAL/KEYPAD/Keypad_interface.h"


#define _7_seg_port 	PORTD_ID

int main()
{
	Keypad_init();
	GPIO_init();

	static char lookUpTable [] ={0x3F , 0x06 , 0x5B , 0x4F , 0x66 , 0x6D , 0x7C , 0x07 , 0x7F , 0x67}; // to control 7 segment
	GPIO_WritePort(_7_seg_port , lookUpTable[0]);
 	uint8 Keypad_value  ;
	uint8 port_value_for_7_seg = 0;
	while(1)
	{
 		 Keypad_value = Keypad_GetPressedKey();
 		 if(Keypad_value>= 0 && Keypad_value<=9)
 		 {
			port_value_for_7_seg = lookUpTable[Keypad_value] | 0x80 ;
			GPIO_WritePort(_7_seg_port , port_value_for_7_seg);
 		 }

	}


}
