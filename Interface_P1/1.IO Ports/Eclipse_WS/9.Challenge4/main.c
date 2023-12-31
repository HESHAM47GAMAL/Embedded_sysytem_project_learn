/*
 * main.c
 *
 *  Created on: Dec 31, 2023
 *      Author: moham
 */

#include <avr/io.h>


int main()
{
	DDRC &= ~(1 << PC0); //configure pin 0 in PORTC as input pin to connect to PIR sensor
	PORTC &= ~(1 << PC0); // Disable internal pull up resistor

	DDRB |= (1 << PB0); // configure pin 0 in PORTB as output pin to connect to led
	PORTB &= ~(1 << PB0);

	while(1)
	{
		if(PINC & (1 << PC0)) //there are motion detection
		{
			PORTB |= (1 << PB0); //turn on led
		}
		else
		{
			PORTB &= ~(1 << PB0);
		}
	}
}
