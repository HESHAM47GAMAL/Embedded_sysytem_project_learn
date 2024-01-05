/*
 * main.c
 *
 *  Created on: Jan 4, 2024
 *      Author: moham
 */

#include <avr/io.h>
#include <avr/interrupt.h>

#define NUM_interrupt_for_Delay 20

char actual_interrupt_happen = 0;

ISR(TIMER0_COMP_vect)
{
	actual_interrupt_happen ++;
	if(actual_interrupt_happen == 20)
	{
		actual_interrupt_happen = 0; //reset counter
		PORTC ^= (1 << PC0);
		PORTA ^= (1 << PA0);
	}

}

//Resolution = 1024/ (8*10^6) = 128 us
//Toverflow = 128 * 256 = 32.768 ms
//
//using OCR0
//
//Toverflow = 128us * 196 ~= 25ms
//----> So ->> to make delay half second = 20 compare match to make Delay

void Timer0_CTC_init(unsigned char compare_Tick)
{
	SREG |= (1 << 7); //Enable Global interrupt

	/***     set this pin for non PWM          ***/
	TCCR0 |= (1 << FOC0);

	/***     Set CTC mode         ***/
	TCCR0 |= (1 << WGM01);
	TCCR0 &= ~(1 << WGM00);

	OCR0 = compare_Tick;

	/***     Enable compare match mode interrupt    ***/
	TIMSK |= (1 << OCIE0);

	/***     Set Prescaler   1024    ***/
	TCCR0 |= (1 << CS00);
	TCCR0 &= ~(1 << CS01);
	TCCR0 |= (1 << CS02);

}

int main()
{
	DDRC |= (1 << PC0); //Configure PiN 0 in PORTC as output  to connect led
	PORTC &= ~(1 << PC0);   // clear Pin 0 in PORTC (LED OFF) as connected positive logic

	DDRA |= (1 << PA0);
	PORTA |= (1 << PA0);
	Timer0_CTC_init (196);
	while(1)
	{

	}

}


