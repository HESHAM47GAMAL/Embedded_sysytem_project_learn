/*
 * main.c
 *
 *  Created on: Jan 8, 2024
 *      Author: moham
 */
#include <avr/io.h>

#define F_CPU 8000000UL

#include <util/delay.h>


void ServoAngle(unsigned char Angle)
{
	if(Angle < 0)
	Angle = 0 ;
	else if(Angle > 180)
	Angle = 180;
	OCR1A = 60 + (1.4 * Angle);
}

//As F_cpu = 8MHZ and Servo frequency required = 50HZ
//F_pwm = F_clk / (N * (1 + TOP_value))
//edit equation  (N * (1 + TOP_value)) = F_clk / F_pwm = (8* 10^6) / 50 = 160 *10^3
//So I want try way to get prepor frequency for Servo so I will use Prescaler make me able to get suitable value for (1 + TOP_value)= ICR
//(N * (1 + TOP_value)) =  160 *10^3
//if use prescaler 64 So (1 + TOP_value) = 2500
//So Top value = 2499 that will assigned to ICR1


/***          From Data Sheet but can't get 0 OR 180 degree              ***/
//in this hard case 🥲 tick = prescaler / F_CPU = 64 / (8*10^6) = 8us‍
//Servo need frequency = 50HZ and need Dury cycle time = 1 : 2 ms 🙆‍♂️
//		|
//		|
//		|
//		\/
//	OCR1 value = 125	: 250
//	to get 		 1ms	: 2ms
//  Angle 		 -90	  90


/****       So After some tries get that   in Real World ****/

//	OCR1 value = 60	: 310
//	to get 		 0.48ms	: 2.48ms
//  Angle 		 -90	  90
//in Real world	  0		: 180


void Timer1_Fast_PWM_init(void)
{
	/***    Clear this bit as use PWM mode         ***/
	TCCR1A &= ~(1 << FOC1A);

	/***   set mode Fast PWM that TOP value = ICR1   , That is Mode 14 in Timer1      ***/
	TCCR1A &= ~(1 << WGM10);
	TCCR1A |= (1 << WGM11);
	TCCR1B |= (1 << WGM12);
	TCCR1B |= (1 << WGM13);

	/***    use Non inverting PWM mode         ***/
	TCCR1A |= (1 << COM1A1);
	TCCR1A &= ~(1 << COM1A0);

	/***    set initial value for Timer 1 register         ***/
	TCNT1 = 0;

	/***    Set value of ICR1        ***/
	ICR1 = 2499 ;

// 	/***    Set value for compare register       ***/
// 	OCR1A = 188;

	/***    use funcion control angle  ***/
	ServoAngle(0);

	/***    Set Prescaler that will e 64     ***/
	TCCR1B |= (1 << CS10) | (1 << CS11);
	TCCR1B &= ~(1 << CS12);



}


int main()
{
	DDRD |= (1 << PD5); // Configure pin 5 in PORTD as output pin to connect to Servo motor
	Timer1_Fast_PWM_init();


	while(1)
	{
		for(short angle = 0 ; angle <= 180 ; angle++)
		{
			ServoAngle(angle);
			_delay_ms(10);
		}
		for(short angle = 179 ; angle >= 1 ; angle--)
		{
			ServoAngle(angle);
			_delay_ms(10);
		}

	}

}


