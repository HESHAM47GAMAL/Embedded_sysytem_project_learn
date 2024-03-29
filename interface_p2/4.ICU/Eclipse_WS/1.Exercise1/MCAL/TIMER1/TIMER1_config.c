 /******************************************************************************
 *
 * Module: TIMER0
 *
 * File Name: TIMER0_config.c
 *
 * Description: include configuration that will applied
 *
 * Author: Hesham Shehata
 *
 *******************************************************************************/

/**************************                   INCLUDES                   **************************/
#include "TIMER1_config.h"


/*  fill this data from available option in     TIMER0_config.h     */


#if(TIMER1_CURRENT_MODE == T1_NORMAL_MODE)

    TIMER1_ConfigType TIMER1_ConfigTypeParam = {
        F_CPU_8_T1    ,    /*    Choose Prescaler   */
    };
    
#elif(TIMER1_CURRENT_MODE == T1_CTC_MODE )

    TIMER1_ConfigType TIMER1_ConfigTypeParam = {
        F_CPU_8_T1   ,     /*    Choose Prescaler   */ 
        T1_TOP_equal_OCR1A ,  /*    Choose Top value   */ 
        T1_TOGGLE_CO1      /*    Choose what happen on compare match   */ 
    };


#elif( (TIMER1_CURRENT_MODE == T1_FAST_PWM_MODE) || (TIMER1_CURRENT_MODE == T1_PHASE_CORRECT_PWM_MODE))
 
    TIMER1_ConfigType TIMER1_ConfigTypeParam = {
        F_CPU_8_T1   ,     /*    Choose Prescaler   */ 
        T1_TOP_equal_1FF ,      /*    Choose Top value   */ 
        T1_NON_INVERTING      /*    Choose what happen on compare match   */ 
    };

#elif (TIMER1_CURRENT_MODE == T1_PHASE_FREQUENCY_CORRECT_PWM_MODE)


    TIMER1_ConfigType TIMER1_ConfigTypeParam = {
        F_CPU_8_T1   ,     /*    Choose Prescaler   */ 
        T1_TOP_equal_ICR1 ,      /*    Choose Top value   */ 
        T1_NON_INVERTING      /*    Choose what happen on compare match   */ 
    };


#endif