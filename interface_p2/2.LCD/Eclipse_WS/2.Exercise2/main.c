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
	LCD_DisplayStringRowCol("Welcome To LCD",0,0);
	_delay_ms(3000);
	LCD_DisplayStringRowCol("4 Bit Data Mode",1,0);



	while(1)
	{

	}

}
