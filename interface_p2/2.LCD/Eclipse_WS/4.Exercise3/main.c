/*
 * main.c
 *
 *  Created on: Jan 22, 2024
 *      Author: moham
 */

/**************************                   INCLUDES                   **************************/
#include "MCAL/GPIO/GPIO_interface.h"
#include "HAL/KEYPAD/Keypad_interface.h"
#include "HAL/LCD/LCD_interface.h"
#define F_CPU 8000000UL
#include <util/delay.h>
#define _7_seg_port 	PORTD_ID

uint8 HeartCustomCharacter [] = {0x00 , 0x00 , 0x0A , 0x1F , 0x1F ,0x0E , 0x04 , 0x00};

int main()
{
	Keypad_init();
	GPIO_init();
	LCD_init();
	LCD_GenerateCharacterCGRAM(HeartCustomCharacter , LCD_CGRAM_LOCATION_1);

	LCD_DisplayStringRowCol("Store Custom",0,2);
	LCD_DisplayStringRowCol("char In CGRAM",1,2);
	_delay_ms(8000);

	static char lookUpTable [] ={0x3F , 0x06 , 0x5B , 0x4F , 0x66 , 0x6D , 0x7C , 0x07 , 0x7F , 0x67}; // to control 7 segment
	GPIO_WritePort(_7_seg_port , lookUpTable[0]);
 	uint8 Keypad_value  ;
	uint8 port_value_for_7_seg = 0;
	LCD_ClearScreen();
	LCD_DisplayStringRowCol("I ",0,2);
	LCD_DisplayCustomCharacter(LCD_CGRAM_LOCATION_1);
	LCD_DisplayString(" Embedded");
	_delay_ms(8000);
	LCD_ClearScreen();
	
	while(1)
	{
 		 Keypad_value = Keypad_GetPressedKey();

		port_value_for_7_seg = lookUpTable[Keypad_value] | 0x80 ;
		GPIO_WritePort(_7_seg_port , port_value_for_7_seg);
		
		if(Keypad_value == 4)
		{
			LCD_MoveCursorLeft();
		}	
		else if(Keypad_value == 6)
		{
			LCD_MoveCursorRight();
		}
		else if(Keypad_value == 1)
		{
			LCD_ShitEntireDisplayLeft();
		}
		else if(Keypad_value == 3)
		{
			LCD_ShitEntireDisplayRight();
		}
		else if(Keypad_value == 5)
		{
			LCD_DisplayCustomCharacter(LCD_CGRAM_LOCATION_1);
		}
		else if(Keypad_value == 2)
		{
			LCD_ClearScreen();
		}
		else if(Keypad_value == 8)
		{
			LCD_DisplayStringRowCol("Hesham",0,5);
			LCD_DisplayStringRowCol("Shehata",1,5);
		}

	}


}
