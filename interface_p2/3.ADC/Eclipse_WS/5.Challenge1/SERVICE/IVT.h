/******************************************
* Module: Interrupt Vector Table 
*
* File Name: IVT.h
*
* Description: header file for AVR macros for ISR
*
* Author: Hesham Shehata
*
******************************************/


#ifndef IVT_H_
#define IVT_H_


/**********************************************************
* 						Definition 						  *
**********************************************************/

 #define RESET_vect      			__vector_0
 #define INT0_vect 					__vector_1
 #define INT1_vect 					__vector_2
 #define INT2_vect 					__vector_3
 #define TIMER_2_COMP_vect           __vector_4
 #define TIMER_2_OVF_vect			__vector_5
 #define TIMER_1_CAPT_vect       	__vector_6
 #define TIMER_1_COMPA_vect     		__vector_7
 #define TIMER_1_COMPB_vect  		__vector_8
 #define TIMER_1_OVF_vect			__vector_9
 #define TIMER_0_COMP_vect			__vector_10
 #define TIMER_0_OVF_vect 			__vector_11
 #define SPI_STC_vect   				__vector_12
 #define USART_RXC_vect				__vector_13
 #define USART_UDRE_vect				__vector_14
 #define USART_TXC_vect				__vector_15
 #define ADC_vect                    __vector_16
 #define EE_READY_vect				__vector_17
 #define ANA_COMP_vect				__vector_18
 #define TWI_vect					__vector_19
 #define SPM_RDY_vect				__vector_20
 
 
 #define ISR(INT_VECT)  void INT_VECT (void) __attribute__((signal,used)); \
 void INT_VECT (void)

/**********************************************************
*          Assembly Enable/Disable Global Interrupt		  *
**********************************************************/

/* Assembly function to Enable Global Interrupt*/
 #define sei() __asm__ __volatile__ ("sei" ::: "memory");
 
 /* Assembly function to Disable Global Interrupt*/
 #define cli() __asm__ __volatile__ ("cli" ::: "memory");
 
 

#endif /* IVT_H_ */
