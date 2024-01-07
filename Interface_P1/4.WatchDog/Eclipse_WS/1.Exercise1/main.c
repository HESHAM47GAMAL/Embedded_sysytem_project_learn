/*
 * main.c
 *
 *  Created on: Jan 7, 2024
 *      Author: moham
 */
#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>


void WatchDog_on(void)
{
	/****       Enable watch dog timer              ****/
	WDTCR |= (1 << WDE);

	/****       Set Timeout period           ****/
	WDTCR |= (1 << WDP0) | (1 << WDP1) | (1 << WDP2) ; /// Timeout period = 2.1s
}



/*
 * To Disable watchDog timer follow this steps
 * 1.write logic 1 to WDTOE & WDE in same operation
 * 2.within 4 clock cycle  write 0 in WDE
 */
void watchDog_off(void)
{
	WDTCR |= (1 << WDTOE) | (1 << WDE) ;

	WDTCR &= ~(1 << WDE);

}

int main()
{
	DDRA = 0x03 ; // set pin 0 & 1 in PORTA as output pin
	DDRD |= (1 << PD7); //set pin 7 in PORTD as output pin


	PORTA |= (1 << PA0);
	_delay_ms(500);
	PORTA &= ~(1 << PA0), PORTA |= (1 << PA1);
	_delay_ms(500);
	PORTA &= ~(1 << PA1);

	WatchDog_on();

	PORTD ^= (1 << PD7);
	_delay_ms(1000);

	/***     To test Watch Dog make next line commented as timeout will expired and make Reset OR can uncomment next line to disable watchdog before time expiration              ***/
	//  watchDog_off();
	PORTD ^= (1 << PD7);

	while(1)
	{
		_delay_ms(200);
		PORTD ^= (1 << PD7);
	}


}

