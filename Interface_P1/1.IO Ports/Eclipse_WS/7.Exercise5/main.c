/*
 * main.c
 *
 *  Created on: Dec 30, 2023
 *      Author: moham
 */

#include <avr/io.h>

#include <util/delay.h>

char lookUpTable [] ={0x3F , 0x06 , 0x5B , 0x4F , 0x66 , 0x6D , 0x7C , 0x07 , 0x7F , 0x67};

int main(void)
{
	/* If use bCD 7447*/
//	DDRD &= ~(1 << PD4); //configure pin 4 in PORTD as input pin to connect to Push button
//	PORTD &= ~(1 << PD4); // disable internal pull up resistor
//
//	DDRC |= 0x0F ;// configure first 4 pins in PORTC as output pins to connect with BCD 7447 to connect with Common anode 7 seg
//
//	unsigned char value = 0 ;
//	PORTC = ( PORTC & ~(0x0F) ) | value ;
//	char isPressed_flag = 0;
//	while(1)
//	{
//		if(PIND & (1 << PD4))
//		{
//			_delay_ms(50); // avoid switch bounce period
//			if(PIND & (1 << PD4))
//			{
//				if(isPressed_flag == 0)
//				{
//					isPressed_flag = 1;
//					value++;
//					if(value == 10)
//						value = 0;
//					PORTC = ( PORTC & ~(0x0F) ) | value ;
//				}
//			}
//		}
//		else
//		{
//			isPressed_flag = 0;
//		}
//
//	}


/*************** If use 7 segment direct ************************/


	DDRD = 0xFF ; // configure all port as output to connect with 7-segment
	PORTD = lookUpTable[0] | 0x80 ; // to init 7-seg with 0

	DDRC &= ~(1 << PC0); //configure as input pin to connect with Push Button
	PORTC &= ~(1 << PC0);

	char index = 0;
	char isPressed_flag = 0;
	while(1)
	{
		if(PINC & (1 << PC0))
		{
			_delay_ms(50);
			if(PINC & (1 << PC0))
			{
				if(isPressed_flag == 0)
				{
					isPressed_flag = 1 ;
					index++;
					if(index == 10)
						index = 0 ;
					PORTD = (lookUpTable[index] | 0x80) ;
				}
			}
		}
		else
		{
			isPressed_flag = 0;
		}
	}

}

