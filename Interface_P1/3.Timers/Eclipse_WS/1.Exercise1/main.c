/*
 * main.c
 *
 *  Created on: Jan 3, 2024
 *      Author: moham
 */
#include <avr/io.h>

void TimerDelay(void)
{
	TCNT0 = 0 ; //set intail value for timer register

	/***        Normal Mode       ***/
	TCCR0 &= (1 << WGM00);
	TCCR0 &= (1 << WGM01);

	TCCR0 |= (1 << FOC0); //for non PWM mode

	/***     Set Prescaler       ***/
	TCCR0 |= (1 << CS00);
	TCCR0 &= ~(1 << CS01);
	TCCR0 |= (1 << CS02);

	/*    Disable Overflow Interrupt   */
	TIMSK &= ~(1 << TOIE0);


	/**         Poll Technique                    **/
	while(! ( TIFR & (1 << TOV0)) );  //wait until overflow occur

	TIFR |= (1 << TOV0) ; // clear flag by write value one

	/*     No clock source to stop Timer*/
	TCCR0 &= ~(1 << CS00);
	TCCR0 &= ~(1 << CS01);
	TCCR0 &= ~(1 << CS02);

}



int main()
{
	DDRC |= (1 << PC0); //Configure PiN 0 in PORTC as output  to connect led
	PORTC &= ~(1 << PC0);   // clear Pin 0 in PORTC (LED OFF) as connected positive logic

	DDRA |= (1 << PA0);
	PORTA |= (1 << PA0);



	while(1)
	{
		PORTC ^= (1 << PC0);
		PORTA ^= (1 << PA0);
		for(char i = 0 ; i < 15 ; i++)
		{
			TimerDelay();
		}

	}


}

