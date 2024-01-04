/*
 * main.c
 *
 *  Created on: Jan 2, 2024
 *      Author: moham
 */


#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

ISR(INT0_vect)
{
	SREG |= (1 << 7); // there is need to this as there are not maskable interrupt has priority higher than EXT INT0
	char value = 1 ;
	PORTB = ( PORTB & 0xF0) | (value & 0x0F) ;
	_delay_ms(3000);
	for(char i = 0 ; i < 3 ; i++)
	{
		value <<=1 ;
		PORTB = ( PORTB & 0xF0) | (value & 0x0F) ;
		_delay_ms(3000);
	}
	PORTB = ( PORTB & 0xF0);
}

ISR(INT1_vect)
{
	SREG |= (1 << 7);
	PORTA = 0x01;
	_delay_ms(1500);
	for(char i = 0 ; i < 7 ; i++)
	{
		PORTA <<= 1;
		_delay_ms(1500);
	}
	PORTA = 0x00;

}


void INT0_init(void) //Enable Global and external 0 interrupt and configure it
{
	SREG &= ~(1 << 7); //Disable Global Interrupt
	DDRD &= ~(1 << PD2) ;//configure Pin 2 in portD that have External INT0 to input pin
	PORTD &= ~(1 << PD2);
	GICR |= (1 << INT0); //Enable External interrupt 0
	//As interrupt Pin INT0 -- connected --> to button using pull down resistor
//	  pressed          not pressed
//	  	  |					|
//		  |					|
//		  \/				\/
//		  1					0
	//Sooo configure Event trigger for Interrupt to Rising Edge
	MCUCR |= (1 << ISC01);//configure interrupt trigger to Rising edge
	MCUCR |= (1 << ISC00);
	SREG |= (1 << 7); //Enable Global Interrupt after configuration to avoid any interrupt happen during configuration
}

void INT1_init(void)
{
	SREG &= ~(1 << 7); //disable global interrupt until configure all EXT INT1
	DDRD &= ~(1 << PD3) ; //configure pin 3 in PORTD as input pin as used as external interrupt 1
	PORTD &= ~(1 << PD3) ; // Enable internal pull up resistor
	//As interrupt Pin INT1 -- connected --> to button using internal pull up resistor
//	  pressed          not pressed
//	  	  |					|
//		  |					|
//		  \/				\/
//		  0					1
	//Sooo configure Event trigger for Interrupt to falling Edge
	GICR |= (1 << INT1) ; //enable external interrupt 1 EXTINT1
	//cconfigure interrupt event to rising edge
	MCUCR |= (1 << ISC11) ;
	MCUCR |= (1 << ISC10);
	SREG |= (1 << 7); // enable global interrupt
}




int main()
{
	INT0_init() ;
	INT1_init();

	DDRA = 0xFF ;
	PORTA = 0x00;

	DDRB |= 0x0F;
	PORTB &= 0xF0;

	DDRC |= (1 << PC0);
	PORTC &= ~(1 <<PC0);


	while(1)
	{
		PORTC ^= (1 <<PC0);
		_delay_ms(500);
	}


}

