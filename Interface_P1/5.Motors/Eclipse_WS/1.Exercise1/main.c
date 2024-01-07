/*
 * main.c
 *
 *  Created on: Jan 7, 2024
 *      Author: moham
 */
#include <avr/io.h>

#define F_CPU 8000000UL

#include <util/delay.h>

void StopMotor(void)
{
	PORTC &= ~(1 << PC0) & ~(1 << PC1);
}

void ClockWiseMotor(void)
{
	PORTC |= (1 << PC0);
	PORTC &= ~(1 << PC1);
}

void AntiClockWiseMotor(void)
{
	PORTC &= ~(1 << PC0);
	PORTC |= (1 << PC1);
}

int main()
{
	DDRA &= ~(1 << PA0) & ~(1 << PA1) & ~(1 << PA2); // Configure Pin 0 & 1 & 2 in portA as input pin to connect with push button
	PORTA &= ~(1 << PA0) & ~(1 << PA1) & ~(1 << PA2); // disable internal pull up resistor

	DDRC |=  (1 << PC0) | (1 << PC1); // configure pin 0 & 1 in PortC as output pin to connect with L293D to control motor
	PORTC &= ~(1 << PC0) & ~(1 << PC1); // set initial state Stop motor

//	Depend on Proteus connection
//
//	 PC0		PC1  		Motor state
//	  0			 0			  Stop
//	  1			 0			 ClockWise Move
//	  0			 1			Anti-ClockWise Move
//


	while(1)
	{
		if(PINA & (1 << PA0))
		{
			_delay_ms(50);
			if(PINA & (1 << PA0))
			{
				ClockWiseMotor();
			}
		}

		if(PINA & (1 << PA1))
		{
			_delay_ms(50);
			if(PINA & (1 << PA1))
			{
				AntiClockWiseMotor();
			}
		}

		if(PINA & (1 << PA2))
		{
			_delay_ms(50);
			if(PINA & (1 << PA2))
			{
				StopMotor();
			}
		}
	}

}



