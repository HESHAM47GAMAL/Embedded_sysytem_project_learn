/*
 * main.c
 *
 *  Created on: Jan 29, 2024
 *      Author: moham
 */
/**************************                   INCLUDES                   **************************/
#include "MCAL/GPIO/GPIO_interface.h"
#include "MCAL/ADC/ADC_interface.h"
#include "HAL/LCD/LCD_interface.h"
#include "HAL/LM35/LM35_interface.h"


int main (void)
{
	LCD_init();
	ADC_Init();


	LCD_DisplayString("Temp =    C");
	LCD_MoveCursor(0,10);
	LCD_DisplayCharacter(0xDF);
	LCD_DisplayCharacter('C');


	while(1)
	{
		uint8 Temp = LM35_GetTemperature();
		LCD_MoveCursor(0,7);
		LCD_intToString(Temp);
		if(Temp < 100)
		{
			LCD_DisplayString(" ");
		}
	}
}

