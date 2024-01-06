/*
 * main.c
 *
 *  Created on: Jan 6, 2024
 *      Author: moham
 */

#include <avr/io.h>
#include <util/delay.h>

void TIMER0_Fast_PWM(unsigned char value_represent_dutyCycle)
{
	/***       Clear bit FOC0 as use PWM         ***/
	TCCR0 &= ~(1 << FOC0);
	/***       Set Fast PWM mode        ***/
	TCCR0 |= (1 << WGM00) | (1 << WGM01);

	/***       set OC0 pin to non inverting mode        ***/
	TCCR0 |= (1 << COM01);
	TCCR0 &= ~(1 << COM00);

	/***       set value of OCR to set Duty cycle        ***/
	OCR0 = value_represent_dutyCycle;



	/***       Set prescaler F_CPU/8         ***/
	TCCR0 |= (1 << CS01);
	TCCR0 &= ~(1 << CS00);
	TCCR0 &= ~(1 << CS02);
}

int main()
{

	DDRB |= (1 << PB3); // Configure pin 3 in portB to output pin to generate PWM

	TIMER0_Fast_PWM(128);
	_delay_ms(5000);
	TIMER0_Fast_PWM(64);

	while(1)
	{

	}

}
