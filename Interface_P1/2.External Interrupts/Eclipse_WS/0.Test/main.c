/*
 * main.c
 *
 *  Created on: Jan 2, 2024
 *      Author: moham
 */
#include <avr/io.h>
#include <util/delay.h>

int main()
{
	DDRA |= (1 << PA0);
	PORTA &= ~(1 << PA0);
	while(1)
	{
		PORTA ^= (1 << PA0);
		_delay_ms(1500);
	}


}

