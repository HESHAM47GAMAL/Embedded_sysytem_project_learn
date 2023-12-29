/*
 * main.c
 *
 *  Created on: Dec 29, 2023
 *      Author: moham
 */

#include <avr/io.h>

int main(void)
{
	/*****Initialization ****/
	DDRB &= ~ (1 << PB0); /*Configure PIN 0 in PORTB As Input pin to connect with Button*/
	PORTB |= (1 << PB0); /*Activate Internall pull up to Pin 0 in PORTB*/

	//	Not pressed 			pressed   --> as it pull down
	//		|						|
	//		|						|
	//		\/						\/
	//		1						0

	DDRC |= (1 << PC0) ; /*Configure PIN 0 in PORTC as Output Pin to connect with led*/
	PORTC |= (1 << PC0); /*set value for pin to Logic High as "led turn Off" as connect negative logic*/
	//	value on pin    1		0  as connected 	negative logic
	//					|		|
	//					|		|
	//					\/		\/
	//					Off		on

	while(1)
	{
		/****Application code****/
		if(PINB & (1<< PB0))
		{
			PORTC ^= (1 << PC0);
		}


	}
	return 0;
}
