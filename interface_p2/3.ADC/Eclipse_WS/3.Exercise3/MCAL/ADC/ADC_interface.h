 /******************************************************************************
 *
 * Module: ADC
 *
 * File Name: ADC_interface.h
 *
 * Description: Header contain function prototype to be used 
 *
 * Author: Hesham Shehata
 *
 *******************************************************************************/

//gard file

#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

/**************************                   INCLUDES                   **************************/
#include "../../SERVICE/STD_TYPES.h"
#include "../GPIO/GPIO_interface.h"

/**************************                   Declare custom types                   **************************/
typedef enum
{
    Single_Conversion_Mode ,  // Call function of read ADC value each time you want to know value
    Free_Running_Mode , // once the initial conversion is started, subsequent conversions will automatically start without any additional
    Auto_Trigger_Mode   // convertion happen each time event happen
}ADC_WorkingMode;



//   Note ⛔⛔⛔⛔⛔🙆‍♂️  you need to connect power to AVCC pin in any
typedef enum{
    AREF ,              //      ----|  --> connect wanted reference voltage to this pin
    AVCC ,              //      ----|
    Internal_Voltage =3         // use internal  2.56V
}ADC_ReferenceVoltage ;





/*  this control how 10 bit of ADC convertion stored in 16 bit register*/
typedef enum{
    ADC_Adjust_Right ,  /* Recommended  */
    ADC_Adjust_Left
}ADC_ValueAdjustment ;

/*  As ADC circuit Need 50:200 KHZ So use suitable prescaler to  get this frequency depend on your MCU CLK    */
typedef enum{
    ADC_Divide_By_2 = 1 , ADC_Divide_By_4 , ADC_Divide_By_8 , ADC_Divide_By_16 , ADC_Divide_By_32 , ADC_Divide_By_64 , ADC_Divide_By_128
}ADC_PrescalerSelect;

/*  Note ⛔🙆‍♂️ it will ignored if not use Auto_Trigger_Mode */
/*  So if not use  Auto_Trigger_Mode  write NO_NEED*/
typedef enum 
{
    NO_NEED ,
    Analog_Comparator =  1 , 
    External_Interrupt_Request_0 , 
    Timer_Counter_0_Compare_Match ,
    Timer_Counter_0_Overflow ,
    Timer_Counter_1_Compare_Match_B ,
    Timer_Counter_1_Overflow ,
    Timer_Counter_1_Capture_Event
}ADC_AutoTriggerSource;


typedef struct 
{
    ADC_WorkingMode         ADC_WorkingMode_value;
    ADC_ReferenceVoltage    ADC_ReferenceVoltage_Value ;
    ADC_ValueAdjustment     ADC_ValueAdjustment_value;
    ADC_PrescalerSelect     ADC_PrescalerSelect_value;
    ADC_AutoTriggerSource   ADC_AutoTriggerSource_value;
}ADC_ConfigType ;


/**************************                   Definition                   **************************/

#define ADC_Channel_0       PIN0_ID
#define ADC_Channel_1       PIN1_ID
#define ADC_Channel_2       PIN2_ID
#define ADC_Channel_3       PIN3_ID
#define ADC_Channel_4       PIN4_ID
#define ADC_Channel_5       PIN5_ID
#define ADC_Channel_6       PIN6_ID
#define ADC_Channel_7       PIN7_ID



#define ADC_MAX_VALUE   1023


#define ADLAR   5
#define ADEN    7
#define ADATE   5
#define ADTS0   5
#define ADTS1   6
#define ADTS2   7
#define ADPS0   0
#define ADPS1   1
#define ADPS2   2
#define ADSC    6
#define ADIF    4
#define ADIE    3


void ADC_Init(void);


uint16 ADC_ReadChannelSingleConvertion(uint8 Channel_NUM);

void ADC_FreeRunningStart (uint8 Channel_NUM);

uint16 ADC_ReadConversionRegister(void);


#endif