/*
 * main.c
 *
 *  Created on: Dec 31, 2023
 *      Author: moham
 */
#include <avr/io.h>
#include <util/delay.h>

char lookUpTable [] ={0x3F , 0x06 , 0x5B , 0x4F , 0x66 , 0x6D , 0x7C , 0x07 , 0x7F , 0x67};

int main()
{
//	DDRA &= ~(1 << PA0) & ~(1 << PA1); //configure pin 0 7 1 in PORTA as input to connect with push button
//	PORTA &= ~(1 << PA0) & ~(1 << PA1); //disable for internal pull up resistor
//
//	DDRD |= 0x0F ;
//	unsigned char value = 0 ; //will carry value that will display in 7-segment
//	PORTD = (PORTD & 0xF0) | (value | 0xF0); //
//
//	while(1)
//	{
//		if(PINA & (1 << PA0))//increase Button
//		{
//			_delay_ms(50);// avoid Bounce period
//			if(PINA & (1 << PA0))
//			{
//				if(value != 9)
//				{
//					value ++ ;
//					PORTD = (PORTD & 0xF0) | (value | 0xF0);
//				}
//			}
//			while(PINA & (1 << PA0));
//		}
//
//		if(PINA & (1 << PA1))//Decrease Button
//		{
//			_delay_ms(50);
//			if(PINA & (1 << PA1))
//			{
//				if(value != 0)
//				{
//					value--;
//					PORTD = (PORTD & 0xF0) | (value | 0xF0);
//				}
//			}
//			while(PINA & (1 << PA1));
//		}
//	}

/*************** If use 7 segment direct ************************/

	DDRD = 0xFF ;
	char index = 0 ;
	PORTD = lookUpTable[(short)index] | 0x80 ;

	DDRA &= ~(1 << PA0) & (1 << PA1) ;
	PORTA &= ~(1 << PA0) & (1 << PA1);

		while(1)
		{
			if(PINA & (1 << PA0))//increase Button
			{
				_delay_ms(50);// avoid Bounce period
				if(PINA & (1 << PA0))
				{
					if(index != 9)
					{
						index ++ ;
						PORTD = lookUpTable[(short)index] | 0x80 ;
					}
				}
				while(PINA & (1 << PA0));
			}

			if(PINA & (1 << PA1))//Decrease Button
			{
				_delay_ms(50);
				if(PINA & (1 << PA1))
				{
					if(index != 0)
					{
						index--;
						PORTD = lookUpTable[(short)index] | 0x80 ;
					}
				}
				while(PINA & (1 << PA1));
			}
		}
}


