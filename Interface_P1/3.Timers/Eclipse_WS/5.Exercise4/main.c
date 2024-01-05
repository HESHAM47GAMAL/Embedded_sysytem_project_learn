/*
 * main.c
 *
 *  Created on: Jan 5, 2024
 *      Author: moham
 */

#include <avr/io.h>

//	F_oc = F_clk_i_o   /    2*N*(1 + OCR0)

void Timer0_Wave_generate(unsigned char Ticks_num)
{
	/***     set this pin for non PWM          ***/
	TCCR0 |= ( 1 << FOC0);

	/***     set Timer 0 to CTC mode       ***/
	TCCR0 |= (1 << WGM01);
	TCCR0 &= ~(1 << WGM00);

	/***     Toggle OC0 on compare match         ***/
	TCCR0 |= (1 << COM00);
	TCCR0 &= ~(1 << COM01);

	/***     set Initial value          ***/
	TCNT0 = 0;

	/***     Compare Value          ***/
	OCR0 = Ticks_num ;

	/***     set Prescaler          ***/
	TCCR0 |= (1 << CS00);
	TCCR0 &= ~(1 << CS01);
	TCCR0 &= ~(1 << CS02);


}


int main()
{

	DDRB |= (1 << PB3);
	PORTB &= ~(1 << PB3);

	Timer0_Wave_generate(249); // Generate WaveForm with F = 2 KHZ


	while(1)
	{

	}

}

