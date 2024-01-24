/*
 * main.c
 *
 *  Created on: Jan 24, 2024
 *      Author: moham
 */


#include "MCAL/GPIO/GPIO_interface.h"
#include "HAL/LCD/LCD_interface.h"


#include <util/delay.h>

int main (void)
{
	LCD_init();
	LCD_DisplayStringRowCol("My LCD Driver",0,2);
	_delay_ms(3000);
	LCD_DisplayStringRowCol("Embedded SW",1,2);



	while(1)
	{

	}

}
