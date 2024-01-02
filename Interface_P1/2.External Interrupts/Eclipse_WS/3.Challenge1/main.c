/*
 * main.c
 *
 *  Created on: Jan 2, 2024
 *      Author: moham
 */

#include <avr/io.h>
#include <avr/interrupt.h>

char _7_seg_value = 0;

ISR(INT2_vect)
{
	_7_seg_value++ ;
	if(_7_seg_value == 10)
		_7_seg_value = 0 ;
	PORTC = (PORTC & 0xF0) | (_7_seg_value & 0x0F);
}

void INT2_init( void)
{
	SREG &= ~(1 << 7); // disable global interrupt until finish configuration of Ext INT2
	DDRB &= ~(1 << PB2); // configure pin 2 in PORTB as input as used as external interrupt
	PORTB &= ~(1 << PB2); // disable internal pull up resistor
	GICR |= (1 << INT2); // enable EXT INT2
	MCUCSR |= (1 << ISC2); //configure interrupt event for Rising edge
	SREG |= (1 << 7); // enable global interrupt
}


int main()
{
	INT2_init();

	DDRC |= 0x0F; //Configure first 4 pins in PORTC as output pin to connect with 7447 to connect with 7-segment common anode

	PORTC = (PORTC & 0xF0) | (_7_seg_value & 0x0F);



	while(1)
	{

	}


}

