/*
 * main.c
 *
 *  Created on: Jan 6, 2024
 *      Author: moham
 */

#include <avr/io.h>
#include <avr/interrupt.h>

char tick_num = 0;

ISR(TIMER1_COMPA_vect)
{
	tick_num++;
	if(tick_num == 1)
	{
		OCR1A = 375 ;
		PORTC ^= (1 << PC0);
	}
	else if(tick_num == 2)
	{
		OCR1A = 125 ;
		PORTC ^= (1 << PC0);
		tick_num= 0;
	}

}

void Timer1_CTC_init(void)
{
	/***       Enable Global interrupt bit          ***/
	SREG |= (1 << 7);

	/***       As I will use CTC mode set bit     FOC1A     ***/
	TCCR1A |= (1 << TCCR1A);

	/***       Set CTC mode         ***/
	TCCR1A &= ~(1 << WGM10);
	TCCR1A &= ~(1 << WGM11);
	TCCR1B |= (1 << WGM12);
	TCCR1B &= ~(1 << WGM13);

	/***      Here i will use CTC mode to generate PWM signal on PC0 so I will not use   OC1A or OC1B       ***/
	TCCR1A &= ~(1 << COM1B0) & ~(1 << COM1B1) & ~(1 << COM1A0) & ~(1 << COM1A1);

	/***       Set initial value for Timer register          ***/
	TCNT1 = 0;

	/***       Set value that will compare happen          ***/
	OCR1A = 125 ;

	/***       Enable interrupt of compare match  A         ***/
	TIMSK |= (1 << OCIE1A);

	/***       Set Prescaler    8      ***/
	TCCR1B &= ~(1 << CS10);
	TCCR1B |= (1 << CS11);
	TCCR1B &= ~(1 << CS12);
}


int main()
{
	DDRC |= (1 << PC0);
	PORTC |= (1 << PC0); // set at first pin to logic high to  make pin high for 125 tick and low for 375 tick ------> to generate 25% Duty cycle


	Timer1_CTC_init();

	while(1)
	{

	}


}
