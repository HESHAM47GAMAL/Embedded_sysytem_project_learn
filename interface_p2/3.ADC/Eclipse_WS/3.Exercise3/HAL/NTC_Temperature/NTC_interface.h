 /******************************************************************************
 *
 * Module: NTC Temperature Sensor
 *
 * File Name: NTC_interface.h
 *
 * Description:  Header contain function prototype to be used 
 * 
 * Author: Hesham Shehata
 *
 *******************************************************************************/

// Gard file

#ifndef NTC_INTERFACE_H_
#define NTC_INTERFACE_H_

/**************************                   INCLUDES                   **************************/
#include "../../SERVICE/STD_TYPES.h"


/**************************                   Definition                   **************************/
#define C1      (float32)1.009249522e-03
#define C2      (float32)2.378405444e-04
#define C3      (float32)2.019202697e-07


/**************************                   Function Prototype                   **************************/

uint8 NTC_GetTemperature(void);

#endif