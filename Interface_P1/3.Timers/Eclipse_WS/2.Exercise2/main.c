/*
 * main.c
 *
 *  Created on: Jan 4, 2024
 *      Author: moham
 */
#include <avr/io.h>
#include <avr/interrupt.h>

#define Number_of_Overflow_for_half_second 15

char counter = 0;

ISR(TIMER0_OVF_vect)
{
	counter ++ ;
	if(counter == Number_of_Overflow_for_half_second)
	{
		PORTC ^= (1 << PC0);
		PORTA ^= (1 << PA0);
		counter = 0;
	}

}

void Timer0Init(void)
{
	/***     Enable Global interrupt enable bit        ***/
	SREG |= (1 << 7);

	TCNT0 = 0 ; //set intail value for timer register

	/***        Normal Mode       ***/
	TCCR0 &= (1 << WGM00);
	TCCR0 &= (1 << WGM01);

//	TCCR0 |= (1 << FOC0); //for non PWM mode

	/***     Set Prescaler       ***/
	TCCR0 |= (1 << CS00);
	TCCR0 &= ~(1 << CS01);
	TCCR0 |= (1 << CS02);

	/***     Set Prescaler       ***/
	TIMSK |= (1 << TOIE0);

}



int main()
{
	DDRC |= (1 << PC0); //Configure PiN 0 in PORTC as output  to connect led
	PORTC &= ~(1 << PC0);   // clear Pin 0 in PORTC (LED OFF) as connected positive logic

	DDRA |= (1 << PA0);
	PORTA |= (1 << PA0);
	Timer0Init();



	while(1)
	{


	}


}



