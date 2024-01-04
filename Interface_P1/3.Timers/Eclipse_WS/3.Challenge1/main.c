/*
 * main.c
 *
 *  Created on: Jan 4, 2024
 *      Author: moham
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#define NUM_OVF_for_second 123

/*******************************************
 * 		Using BCD 7447
*******************************************/
//
//char _7_seg_number =0 ;
//unsigned char actual_overflow = 0;
//
//ISR(TIMER0_OVF_vect)
//{
//	actual_overflow++;
//	if(NUM_OVF_for_second == actual_overflow)
//	{
//		PORTA ^= (1 << PD0);
//		TCNT0 = 238 ; //set intail value for timer register
//		_7_seg_number++;
//		if(_7_seg_number == 10)
//			_7_seg_number =0;
//		PORTC = (PORTC & 0xF0) | (_7_seg_number & 0x0F);
//
//		actual_overflow = 0; // reset counter of interrupt happen
//	}
//
//}
//
//
//void Tomer0_OVF_init(void)
//{
//	/***     Enable Global interrupt enable bit        ***/
//	SREG |= (1 << 7);
//
//	TCNT0 = 238 ; //set intail value for timer register
//
//	/***        Normal Mode       ***/
//	TCCR0 &= (1 << WGM00);
//	TCCR0 &= (1 << WGM01);
//
////	TCCR0 |= (1 << FOC0); //for non PWM mode
//
//	/***     Set Prescaler    256   ***/
//	TCCR0 &= ~(1 << CS00);
//	TCCR0 &= ~(1 << CS01);
//	TCCR0 |= (1 << CS02);
//
//	/***     Enable overflow interrupt       ***/
//	TIMSK |= (1 << TOIE0);
//}
//
//int main()
//{
//	DDRC |= 0x0F ; // configure first 4 pins in portC to output pin to connect to 7447 to connect to 7-segment common anode
//	PORTC = (PORTC & 0xF0) ; // initialize 7-segment to display 0
//	Tomer0_OVF_init();
//
//	DDRA |= (1 << PD0);
//
//	while(1)
//	{
//
//	}
//
//}
//
//



/*******************************************
 * 		Without BCD 7447
*******************************************/
char lookUpTable [] ={0x3F , 0x06 , 0x5B , 0x4F , 0x66 , 0x6D , 0x7C , 0x07 , 0x7F , 0x67};

char _7_seg_number =0 ;
unsigned char actual_overflow = 0;

ISR(TIMER0_OVF_vect)
{
	actual_overflow++;
	if(NUM_OVF_for_second == actual_overflow)
	{
		TCNT0 = 238 ; //set intail value for timer register
		_7_seg_number++;
		if(_7_seg_number == 10)
			_7_seg_number =0;
		PORTC = 0x80 | _7_seg_number;

		actual_overflow = 0; // reset counter of interrupt happen
	}

}


void Tomer0_OVF_init(void)
{
	/***     Enable Global interrupt enable bit        ***/
	SREG |= (1 << 7);

	TCNT0 = 238 ; //set intail value for timer register

	/***        Normal Mode       ***/
	TCCR0 &= (1 << WGM00);
	TCCR0 &= (1 << WGM01);

//	TCCR0 |= (1 << FOC0); //for non PWM mode

	/***     Set Prescaler    256   ***/
	TCCR0 &= ~(1 << CS00);
	TCCR0 &= ~(1 << CS01);
	TCCR0 |= (1 << CS02);

	/***     Enable overflow interrupt       ***/
	TIMSK |= (1 << TOIE0);
}

int main()
{
	DDRC |= 0xFF ; // configure first 4 pins in portC to output pin to connect to 7447 to connect to 7-segment common anode
	PORTC = (lookUpTable[_7_seg_number] | 0x80)  ; // initialize 7-segment to display 0
	Tomer0_OVF_init();



	while(1)
	{

	}

}

