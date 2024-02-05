/*
 * main.c
 *
 * Created: 2/4/2024 2:01:28 PM
 *  Author: moham
 */ 

/**************************                   INCLUDES                   **************************/
#include "MCAL/GPIO/GPIO_interface.h"
#include "MCAL/TIMER0/TIMER0_interface.h"
#include "MCAL/TIMER1/TIMER1_interface.h"

#include "MCAL/EXT_INT/EXT_INT_interface.h"
#include "HAL/LCD/LCD_interface.h"

uint8 PWM_LED = 50 ;



uint8 number_of_edges = 0;
uint16 g_timeHigh = 0;
uint16 g_timePeriod = 0 ;
uint16 g_timePeriod_plus_High = 0;

void EgdeProcessing(void)
{
    number_of_edges++;
    if(number_of_edges == 1)
    {
        Timer1_UpdateValue(0);
        Timer1_ICU_capture_edge(Timer1_ICU_capture_Falling_edge);
    }
    else if (number_of_edges == 2)
    {
        g_timeHigh = Icu_getInputCaptureValue();
        Timer1_ICU_capture_edge(Timer1_ICU_capture_Rising_edge);
    }
    else if(number_of_edges == 3)
    {
        g_timePeriod = Icu_getInputCaptureValue();
        Timer1_ICU_capture_edge(Timer1_ICU_capture_Falling_edge);
    }
    else if(number_of_edges == 4 )
    {
        g_timePeriod_plus_High = Icu_getInputCaptureValue();
        Timer1_StopClock();
        Timer1_ICU_capture_edge(Timer1_ICU_capture_Rising_edge);
    }
}

void increase_intensity(void)
{
    if(PWM_LED <= 95)
        PWM_LED += 5;
    Timer0_PhaseCorrectPWMSetDutyCycle(PWM_LED);
}

void Decrease_intensity(void)
{
    if(PWM_LED >= 5)
        PWM_LED -= 5 ;
    Timer0_PhaseCorrectPWMSetDutyCycle(PWM_LED);
}


int main ()
{
	LCD_init();
	// GPIO_init();
	// GPIO_WritePin(PORTD_ID , PIN0_ID, LOGIC_LOW);

    INT0_init(FALLING_EDGE_TRIGGER,INPUT_PIN_PULLUP);
    INT1_init(FALLING_EDGE_TRIGGER,INPUT_PIN_PULLUP);
    INT0_SetCallBack(increase_intensity);
    INT1_SetCallBack(Decrease_intensity);

	
    Timer0_Init();
    Timer0_PhaseCorrectPWMSetDutyCycle(PWM_LED);

	Timer1_Init();
    Timer1_SetCallBack(EgdeProcessing);
    Timer1_ICU_capture_edge(Timer1_ICU_capture_Rising_edge);
    Timer1_ProvideClock();

    uint8 DutyCycle = 0 ;


	while(1)
	{

        if (number_of_edges == 4)
        {
            number_of_edges = 0; 
            DutyCycle = ( (float32)(g_timePeriod_plus_High - g_timePeriod) / (g_timePeriod_plus_High -g_timeHigh) ) * 100 ;
            LCD_MoveCursor(0,0);
            LCD_DisplayString("DUTY = ");
            LCD_intToString(DutyCycle);
            LCD_DisplayCharacter('%');
			LCD_DisplayCharacter(' ');
            g_timeHigh = 0 ;
            g_timePeriod = 0;
            g_timePeriod_plus_High = 0 ;
            Timer1_ProvideClock();
        }   
	}
	
}
