/*
 * main.c
 *
 * Created: 2/4/2024 2:01:28 PM
 *  Author: moham
 */ 

/**************************                   INCLUDES                   **************************/
// #include "MCAL/GPIO/GPIO_interface.h"
// #include "MCAL/TIMER0/TIMER0_interface.h"
#include "MCAL/USART/USART_interface.h"





int main ()
{
	
	
	USART_Init();
//	USART_SendStringPolling(USART_Terminal_clear);
//	USART_SendStringPolling(USART_Terminal_Home_Position);
	USART_SendStringPolling("Hesham Shehata");
	USART_SendStringPolling(USART_Terminal_New_line);
	USART_SendStringPolling("Message Send from ATmega32");
	while(1)
	{


	}
	
	
}
