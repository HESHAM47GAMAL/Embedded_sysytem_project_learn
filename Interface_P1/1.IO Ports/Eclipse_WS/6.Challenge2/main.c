/*
 * main.c
 *
 *  Created on: Dec 30, 2023
 *      Author: moham
 */

#include <avr/io.h>
#include <util/delay.h>


int main()
{
	DDRA &= ~(1 << PA3) & ~(1<< PA4) ; /// Configure Pin 3 & 4 in PORTA as input pin to connect to push button
	PORTA &= ~(1 << PA3) & ~(1<< PA4) ; /// Disable to internal pull up resistor

	DDRD = 0xff; //configure all portD as output pins to connect to led
	PORTD = 0x00 ; // set all pins for PORTD to logic low as all leds are off
	unsigned char value_buttons =0;

	while(1)
	{
		value_buttons = PINA & 0x18;
		if (value_buttons == 0)
		{
			PORTD = 0x00;
		}
		else if(value_buttons == 0x08 || value_buttons == 0x18)// if B1 pressed or b1 & b2 pressed
		{
			_delay_ms(30);
			if(value_buttons == 0x08 || value_buttons == 0x18)//second check to avoid button bouncing time
			{
				PORTD = 0x55 ; //0101 0101  --> mean only even pin will take value logic high
				_delay_ms(500);
				PORTD = 0x00;
				_delay_ms(500);
			}
		}
		else if( value_buttons == 0x10)// if B2 pressed
		{
			_delay_ms(30);
			if(value_buttons == 0x10)//second check to avoid button bouncing time
			{
				PORTD = 0xAA;//1010 1010  --> mean only odd pin will take value logic high
				_delay_ms(500);
				PORTD = 0x00;
				_delay_ms(500);
			}
		}


	}



	return 0;
}


