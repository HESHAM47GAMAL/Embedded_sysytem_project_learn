/*
 * main.c
 *
 *  Created on: Feb 7, 2024
 *      Author: moham
 */



#include "MCAL/USART/USART_interface.h"


int main()
{
	USART_Init();
	uint8 Received_data ;
	while(1)
	{
		/*	Recive data from Terminal from PC */
		Received_data = USART_ReceiveBytePolling();

		/*	Send this data to MCU2  */
		USART_SendBytePolling(Received_data);
	}


}
