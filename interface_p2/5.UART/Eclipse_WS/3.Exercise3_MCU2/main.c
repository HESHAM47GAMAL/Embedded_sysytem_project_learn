/*
 * main.c
 *
 *  Created on: Feb 7, 2024
 *      Author: moham
 */


#include "HAL/LCD/LCD_interface.h"
#include "MCAL/USART/USART_interface.h"
#include "MCAL/GPIO/GPIO_interface.h"
uint8 HeartCustomCharacter [] = {0x00 , 0x00 , 0x0A , 0x1F , 0x1F ,0x0E , 0x04 , 0x00};


int main()
{
	LCD_init();
	USART_Init();
	LCD_GenerateCharacterCGRAM(HeartCustomCharacter , LCD_CGRAM_LOCATION_1);

	LCD_ClearScreen();

	uint8 Received_data ;

	while(1)
	{
		Received_data = USART_ReceiveBytePolling();
		if(Received_data == '@')
			LCD_DisplayCustomCharacter(LCD_CGRAM_LOCATION_1);
		else
			LCD_DisplayCharacter(Received_data);
	}


}


