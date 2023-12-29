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
	DDRB &= ~ (0x03); /*Configure PIN 0 , 1 in PortB as input pin  to connect with Push Button*/
	PORTB &= ~ (0x03); /*Diable pull up resistor to pin 0 , 1 in PortB*/

//	Not pressed 			pressed   --> as it pull down
//		|						|
//		|						|
//		\/						\/
//		0						1

	DDRC |= (0x03); /*Configure PIN 0 , 1 PORTC as output pin*/
	PORTC |= (0x03); /*Set PIN 0 , 1 POrtC to value Zero (Led Off)*/

//	value on pin    1		0
//					|		|
//					|		|
//					\/		\/
//					On		off

	unsigned short PIN_0_1_value =  0;
	unsigned short PORT_0_1_value = 0;
	while(1)
	{
		/****Application code****/
		PIN_0_1_value = PINB & 0x03;  //get only value for button 0 and 1 as pin 0 and 1 and ignore rest
		PORT_0_1_value = ( PORTC & ~(0x03) ) | PIN_0_1_value ;
		PORTC = PORT_0_1_value;

	}


}
