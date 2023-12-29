/*
 * main.c
 *
 *  Created on: Dec 26, 2023
 *      Author: moham
 */


#include <avr/io.h>


int main(void)
{

/* Initialization*/
DDRA &= ~(1 << 3); //Set PORT A PIN 3 as input pin to connect  with switch
PORTA &= ~(1 << 3); //Disable pull up resistor

DDRC |= (1 << 7); //Set PORT C PIN 5 as output pin
PORTC &= ~(1<<7); // initialize as low
while(1)
{
	/* Application Code*/
	if(PINA & (1 << 3))  ///if button pressed
	{
		PORTC |= (1<<7) ; //turn on led
	}
	else ///if button Not pressed
	{
		PORTC &= ~(1<<7); // turn off led
	}

}


}
