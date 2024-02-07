/*
 * main.c
 *
 *  Created on: Feb 7, 2024
 *      Author: moham
 */



#include "MCAL/GPIO/GPIO_interface.h"
#include "MCAL/USART/USART_interface.h"



int main ()
{
	GPIO_init();
	USART_Init();
	GPIO_WritePort(PORTC_ID , 0x00);

	while(1)
	{
		uint8 received_data = USART_ReceiveBytePolling();
//		GPIO_WritePort(PORTC_ID , (1<<received_data));
		GPIO_WritePort(PORTC_ID , 0x00);
		GPIO_WritePin(PORTC_ID,received_data  , LOGIC_HIGH);
	}


}

