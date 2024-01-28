 /******************************************************************************
 *
 * Module: ADC
 *
 * File Name: ADC_config.h
 *
 * Description: Header to configure all ADC 
 *
 * Author: Hesham Shehata
 *
 *******************************************************************************/


//Gard file

#ifndef ADC_CONFIG_H_
#define ADC_CONFIG_H_

/**************************                   INCLUDES                   **************************/
#include "ADC_interface.h"

/*  fill this data from available option in     ADC_interface.h     */

ADC_ConfigType  ADC_ConfigTypeParam ={
	Free_Running_Mode ,  /*    Choose Mode of conversion   */
	AVCC ,        /*    Choose volatge reference used in ADC Conversion     */
	ADC_Adjust_Left ,        /*    Choose Storing of 10 bit ADC value adjusted in 16 bits  */
    ADC_Divide_By_64 ,        /*    Choose prescaler for MCU clock as ADC circuit need to get 50 : 200 KHZ clock to Work correctly  */
    NO_NEED                   /*    If use "Auto Trigger Mode" give trigger source if not use this mode write No Need or any give will ignored  */
};

/*  write value of voltage that will use in pin AVCC OR AREF and Note ⛔🙆‍♂️ will ignored if use internal voltage reference*/
#define REFRENCE_Volt_AVCC_OR_AREF  5

/*  Choose between Enable and Disable ADC Interrupt     */
#define ADC_Interrupt_Enable    1              //  Option 1 ------------
#define ADC_Interrupt_Disable   0              //  Option 2 -----------|  
//                                                                     | Here
#define ADC_Interrupt_State         ADC_Interrupt_Disable  //<----------

#endif
