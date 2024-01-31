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

	DDRC |= (1 << PC0);
	unsigned char intensity ;

	while(1)
	{
		TIMER0_Fast_PWM(255);
		_delay_ms(3000);
		TIMER0_Fast_PWM(0);
		_delay_ms(3000);
//		for(intensity = 0 ; intensity < 255 ; intensity += 5)
//		{
//			TIMER0_Fast_PWM(intensity);
//			_delay_ms(200);
//		}
//		for(intensity = 255 ; intensity > 0 ; intensity -= 5)
//		{
//			PORTC |= (1 << PC0);
//			TIMER0_Fast_PWM(intensity);
//			_delay_ms(200);
//		}

	}

}
