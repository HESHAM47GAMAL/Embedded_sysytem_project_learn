/*
 * main.c
 *
 *  Created on: Jan 26, 2024
 *      Author: moham
 */

/**************************                   INCLUDES                   **************************/
#include "MCAL/GPIO/GPIO_interface.h"
#include "MCAL/ADC/ADC_interface.h"
#include "HAL/LCD/LCD_interface.h"
#define F_CPU 8000000UL
#include <util/delay.h>


int main(){
	LCD_init();
	ADC_Init();
	LCD_DisplayString("POT value : ");

	while(1)
	{
		uint16 Pot = ADC_ReadChannelSingleConvertion(ADC_Channel_0);
		LCD_MoveCursor(0,12);
		LCD_intToString(Pot);
		if(Pot <1000)
		{
			LCD_DisplayString(" ");
		}

	}
}
