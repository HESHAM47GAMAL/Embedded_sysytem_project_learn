 /******************************************************************************
 *
 * Module: ADC
 *
 * File Name: ADC_private.h
 *
 * Description: Header file for AVR contain all register memmory mapped adderess for ADC
 *
 * Author: Hesham Shehata
 *
 *******************************************************************************/

// gard file 

#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_

/**************************                   INCLUDES                   **************************/
#include "../../SERVICE/STD_TYPES.h"


/**************************                   Register memmory mapped GPIO                  **************************/

/*************  Control PortA  	*************/
#define ADMUX            (* (volatile uint8 *) (0x27) )

#define ADCSRA           (* (volatile uint8 *) (0x26) )

#define ADCL             (* (volatile uint8 *) (0x24) )

#define ADCH             (* (volatile uint8 *) (0x25) )

#define SFIOR            (* (volatile uint8 *) (0x50) )

#define ADC_REG          (* (volatile uint16 *) (0x24) )

#endif