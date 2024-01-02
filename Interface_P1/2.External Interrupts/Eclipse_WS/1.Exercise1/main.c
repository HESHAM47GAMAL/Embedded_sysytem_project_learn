/*
 * main.c
 *
 *  Created on: Jan 2, 2024
 *      Author: moham
 */


#include <avr/io.h>
#include <avr/interrupt.h>

ISR(INT0_vect)
{
	PORTC ^= (1 << PC0); //Toggle value for pin to (Toggle led)
}


void INT0_init(void) //Enable Global and external 0 interrupt and configure it
{
	SREG &= ~(1 << 7); //Disable Global Interrupt
	DDRD &= ~(1 << PD2) ;//configure Pin 2 in portD that have External INT0 to input pin
	GICR |= (1 << INT0); //Enable External interrupt 0
	//As interrupt Pin INT0 -- connected --> to button using pull down resistor
//	  pressed          not pressed
//	  	  |					|
//		  |					|
//		  \/				\/
//		  1					0
	//Sooo configure Event trigger for Interrupt to Rising Edge
	MCUCR |= (1 << ISC00) | (1 << ISC01) ;//configure interrupt trigger to Rising edge
	SREG |= (1 << 7); //Enable Global Interrupt after configuration to avoid any interrupt happen during configuration
}



int main()
{
	INT0_init() ;

	DDRC |= (1 << PC0); //Configure Pin 0 in PORTC as output pin to connect to Led
	PORTC |= (1 << PC0); // set pin 0 in portC to logic High to turn led Off as connected using negative logic



	while(1)
	{

	}


}

