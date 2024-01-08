/*
 * main.c
 *
 *  Created on: Jan 8, 2024
 *      Author: moham
 */
#include <avr/io.h>

#define F_CPU 8000000UL

#include <util/delay.h>


// PC0 PC1 PC2 PC3
//	A	A`	B	B`
//	1	0	1	0
//	0	1	1	0
//	0	1	0	1
//	1	0	0	1

// lead to create array with value to make easy use this values to rotate Don't forget this depend on my circuit connection
char FullModeStepper [] = {0x00 , 0x05 , 0x06 , 0x0A , 0x09} ;


int main()
{

	DDRA &= ~(1 << PA2); // configure this pin as input pin to connect with push button using pull down configuration
	PORTA &= ~(1 << PA2); // disable internal pull up resistor

	DDRC |= 0x0F ; // configure first 4 pins in PORTC as output pins
	PORTC &= 0xF0 ; // set initial value zeros for this bits


	char stepAngle = 0;
	while(1)
	{
		if(PINA & (1 << PA2))
		{
			_delay_ms(50);
			if(PINA & (1 << PA2))
			{
				stepAngle++;
				PORTC = (PORTC & 0xF0) | FullModeStepper[stepAngle];
				if(stepAngle == 4)
					stepAngle = 0;
			}
			while(PINA & (1 << PA2));
		}
	}


}

