/*
 * main.c
 *
 *  Created on: Dec 29, 2023
 *      Author: moham
 */

#include <avr/io.h>



#include <util/delay.h>


int main ()
{
	/*****Initialization ****/
	DDRD |= (1 << 6); /*configure pin6 in PORT D as output pin*/
	PORTD &= ~ (1 << 6); /*Set pin value to  high (Led off as connect negative logic)*/

	while(1)
	{
		/**Application code**/
//		PORTD &= ~ (1 << 6);/*Set pin value to  Low (Led on as connect negative logic)*/
//		_delay_ms(1000);
//		PORTD |= (1 << 6);/*Set pin value to  high (Led off as connect negative logic)*/
//		_delay_ms(1000);


		/***********************Another solution*********************************/
		PORTD ^= (1 << 6);
		_delay_ms(1000);
	}

	return 0;
}

