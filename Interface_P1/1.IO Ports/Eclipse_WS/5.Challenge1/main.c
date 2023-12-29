/*
 * main.c
 *
 *  Created on: Dec 29, 2023
 *      Author: moham
 */

#include <avr/io.h>

#include <util/delay.h>


int main(void)
{
	/*****Initialization ****/
	DDRC |= 0xFF ; //Configure PORTC as output as connected to leds
	PORTC = 1 ; //set all pins of port to Zero Led Tun off
	//0000 0001
	//	value on pin    1		0  as connected 	positive logic
	//					|		|
	//					|		|
	//					\/		\/
	//					On		off
	while(1)
	{
		/****Application code****/

		_delay_ms(500);
		PORTC <<= 1;//after 500ms make shift left to  make next pin high of 8 pins and the last is low
//		0000 0001
//		0000 0010
//		0000 0100
//		0000 1000
//		0001 0000
//		0010 0000
//		0100 0000
//		1000 0000
//	  1 0000 0000
		//after 8 shift left PORTC will = 0 as this register only bits
		if(PORTC == 0)
		{
			PORTC = 1; // so set PORTC to 1 to repeat sequence
		}


	}

	return 0;
}
