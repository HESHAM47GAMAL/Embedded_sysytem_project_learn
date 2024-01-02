/*
 * main.c
 *
 *  Created on: Jan 2, 2024
 *      Author: moham
 */

#include <avr/io.h>

#include <avr/interrupt.h>

#include <util/delay.h>

ISR(INT1_vect)
{
	unsigned char T_PORTC = PORTC ;

	for(char i = 0 ; i < 5 ; i++)
	{
		PORTC = 0xFF ;
		_delay_ms(500);
		PORTC = 0X00;
		_delay_ms(500);
	}

	/*** Another code ***/
//	PORTC = 0x00;
//	for(char i = 0 ; i < 10; i++)
//	{
//		PORTC ^= 0xFF;
//		_delay_ms(500);
//	}
	PORTC = T_PORTC;
}

void INT1_init(void)
{
	SREG &= ~(1 << 7); //disable global interrupt until configure all EXT INT1
	DDRD &= ~(1 << PD3) ; //configure pin 3 in PORTD as input pin as used as external interrupt 1
	PORTD |= (1 << PD3) ; // Enable internal pull up resistor
	//As interrupt Pin INT1 -- connected --> to button using internal pull up resistor
//	  pressed          not pressed
//	  	  |					|
//		  |					|
//		  \/				\/
//		  0					1
	//Sooo configure Event trigger for Interrupt to falling Edge
	GICR |= (1 << INT1) ; //enable external interrupt 1 EXTINT1
	//cconfigure interrupt event to Falling edge
	MCUCR |= (1 << ISC11) ;
	MCUCR &= ~(1 << ISC10);
	SREG |= (1 << 7); // enable global interrupt
}


int main()
{
	INT1_init();
	DDRC = 0xFF ; //confifure all pins In PORTC to output pin to connect to leds
	PORTC = 0x00 ; // set all pins in portC to value Zero (turn all led off) as connected using positive logic

	while(1)
	{
		if(PORTC == 0)
			PORTC = 0x01 ;
		_delay_ms(500);
		PORTC <<= 1;


	}


}




/***********************
 * 			 OR
***********************/

//char interrupt_Flag = 0;
//
//ISR(INT1_vect)   // as ISR should be 1.short 2.deterministic 3.fast as possible
//{
//	interrupt_Flag = 1;
//}
//
//void INT1_init(void)
//{
//	SREG &= ~(1 << 7); //disable global interrupt until configure all EXT INT1
//	DDRD &= ~(1 << PD3) ; //configure pin 3 in PORTD as input pin as used as external interrupt 1
//	PORTD |= (1 << PD3) ; // Enable internal pull up resistor
//	//As interrupt Pin INT1 -- connected --> to button using internal pull up resistor
////	  pressed          not pressed
////	  	  |					|
////		  |					|
////		  \/				\/
////		  0					1
//	//Sooo configure Event trigger for Interrupt to falling Edge
//	GICR |= (1 << INT1) ; //enable external interrupt 1 EXTINT1
//	//cconfigure interrupt event to Falling edge
//	MCUCR |= (1 << ISC11) ;
//	MCUCR &= ~(1 << ISC10);
//	SREG |= (1 << 7); // enable global interrupt
//}
//
//
//int main()
//{
//	INT1_init();
//	DDRC = 0xFF ; //confifure all pins In PORTC to output pin to connect to leds
//	PORTC = 0x00 ; // set all pins in portC to value Zero (turn all led off) as connected using positive logic
//
//	while(1)
//	{
//		if(interrupt_Flag == 0)
//		{
//			if(PORTC == 0)
//				PORTC = 0x01 ;
//			_delay_ms(500);
//			PORTC <<= 1;
//		}
//		else if(interrupt_Flag == 1)
//		{
//			interrupt_Flag = 0;
//			unsigned char T_PORTC = PORTC ;
//
//				for(char i = 0 ; i < 5 ; i++)
//				{
//					PORTC = 0xFF ;
//					_delay_ms(500);
//					PORTC = 0X00;
//					_delay_ms(500);
//				}
//
//				/*** Another code ***/
//			//	PORTC = 0x00;
//			//	for(char i = 0 ; i < 10; i++)
//			//	{
//			//		PORTC ^= 0xFF;
//			//		_delay_ms(500);
//			//	}
//				PORTC = T_PORTC;
//		}
//
//
//	}
//
//
//}

