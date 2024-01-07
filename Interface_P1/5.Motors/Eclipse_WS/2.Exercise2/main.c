/*
 * main.c
 *
 *  Created on: Jan 7, 2024
 *      Author: moham
 */

#include <avr/io.h>

#define F_CPU 8000000UL

#include <util/delay.h>


void Timer0_Fast_PWM_init(unsigned char ticks)
{
	/***   Set OC0/PB3  ***/
	DDRB |= (1 << PB3);

	/***   Set fast PWM mode  ***/
	TCCR0 |= (1 << WGM00) | (1 << WGM01);

	/***   initialize timer 0 register  ***/
	TCNT0 = 0 ;

	/***   set fast PWM non converted mode  ***/
	TCCR0 |= (1 << COM01);
	TCCR0 &= ~(1 << COM00);

	/***   Clear bit FOC0 as use PWM mode  ***/
	TCCR0 &= ~(1 << FOC0);

	/***   Set compare value to define Duty cycle  ***/
	OCR0 = ticks ;

	/***   Set Prescaler  to 64 as use FCU = 8 MHZ and want to generate signal with frequncy = 500HZ ***/
	TCCR0 |= (1 << CS00);
	TCCR0 |= (1 << CS01);
	TCCR0 &= ~(1 << CS02);
}

void motor_Speed(unsigned char Duty)
{
	signed  short Assigned_value = ((unsigned short )Duty * 255) / 100;
	if(Assigned_value > 255)
		Assigned_value = 255;
	else if(Assigned_value < 0)
		Assigned_value = 0;
	OCR0 = (unsigned char)Assigned_value;
}



void StopMotor(void)
{
	PORTC &= ~(1 << PC0) & ~(1 << PC1);
}

void ClockWiseMotor(void)
{
	PORTC |= (1 << PC0);
	PORTC &= ~(1 << PC1);
}

void AntiClockWiseMotor(void)
{
	PORTC &= ~(1 << PC0);
	PORTC |= (1 << PC1);
}

int main()
{
	DDRA = 0XE0; // Configure Pin 0 & 1 & 2 & 3 & 4 in portA as input pin to connect with push button
	PORTA = 0XE0; // disable internal pull up resistor

	DDRC |=  (1 << PC0) | (1 << PC1); // configure pin 0 & 1 in PortC as output pin to connect with L293D to control motor
	PORTC &= ~(1 << PC0) & ~(1 << PC1); // set initial state Stop motor

	Timer0_Fast_PWM_init(128) ; // Set duty cycle 50 at first

//	Depend on Proteus connection
//
//	 PC0		PC1  		Motor state
//	  0			 0			  Stop
//	  1			 0			 ClockWise Move
//	  0			 1			Anti-ClockWise Move
//

	unsigned char Speed_DutyCycle = 50 ;

	while(1)
	{
		if(PINA & (1 << PA0))
		{
			_delay_ms(50);
			if(PINA & (1 << PA0))
			{
				ClockWiseMotor();
			}
		}

		if(PINA & (1 << PA1))
		{
			_delay_ms(50);
			if(PINA & (1 << PA1))
			{
				AntiClockWiseMotor();
			}
		}

		if(PINA & (1 << PA2))
		{
			_delay_ms(50);
			if(PINA & (1 << PA2))
			{
				StopMotor();
			}
		}
		if(PINA & (1 << PA3))
		{
			_delay_ms(50);
			if(PINA & (1 << PA3))
			{
				Speed_DutyCycle -= 10;
				motor_Speed(Speed_DutyCycle);
			}
		}

		if(PINA & (1 << PA4))
		{
			_delay_ms(50);
			if(PINA & (1 << PA4))
			{
				Speed_DutyCycle += 10;
				motor_Speed(Speed_DutyCycle);
			}
		}
	}

}




