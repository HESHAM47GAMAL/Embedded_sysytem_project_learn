 /******************************************************************************
 *
 * Module: LCD
 *
 * File Name: LCD_program.c
 *
 * Description: source file for implementation
 *
 * Author: Hesham Shehata
 *
 *******************************************************************************/

/**************************                   INCLUDES                   **************************/
#include "LCD_config.h"
#include "LCD_interface.h"
#include "../../MCAL/GPIO/GPIO_interface.h"
 #include <stdlib.h>
 #include <string.h>

#include <util/delay.h>

/**************************                   Static Variables                  **************************/


static uint8 row_global = 0 ;
static uint8 col_global = 0 ;



/**************************                   Function Implementation                   **************************/

void LCD_init(void)
{
    /*  congfigure RS LCD pin   */
    GPIO_SetPinDirection(LCD_RS_PORT_ID,LCD_RS_PIN_ID,OUTPUT_PIN);
    /*  congfigure R/W LCD pin   */
    GPIO_SetPinDirection(LCD_RW_PORT_ID,LCD_RW_PIN_ID,OUTPUT_PIN);
    /*  congfigure E LCD pin   */
    GPIO_SetPinDirection(LCD_E_PORT_ID,LCD_E_PIN_ID,OUTPUT_PIN);

    /*  Configure pins of Data with LCD     */
    #if(LCD_BITS_MODE == LCD_8_BIT_MODE)
        GPIO_SetPortDirection(LCD_DATA_PORT,OUTPUT_PORT);
        /*  Send command that tell I want to use 8 data pins*/
        LCD_SendCommand(LCD_2_LINE_8_BIT_5x8_DOT) ; 
    #elif(LCD_BITS_MODE == LCD_4_BIT_MODE)
        for(uint8 it = 0 ; it < 4 ;it++)
        {
            GPIO_SetPinDirection(LCD_DATA_PORT,LCD_4_BIT_START_PIN + it,OUTPUT_PIN);
        }
        /*  It's step mandatory in 4 bits data pins*/
        LCD_SendCommand(LCD_RETURN_TO_HOME_IN_SCREEN);
        /*  Send command that tell I want to use 4 data pins*/
        LCD_SendCommand(LCD_2_LINE_4_BIT_5x8_DOT) ; 
    #endif

    /*  Put configuration of Cursor     */
    #if(CURSOR_STATE == CURSOR_OFF)
        LCD_SendCommand(LCD_DISPLAY_ON_CURSOR_OFF);
    #elif(CURSOR_STATE == CURSOR_ON_BLINK)
        LCD_SendCommand(LCD_DISPLAY_ON_CURSOR_ON_BLINKING_ON);
    #elif(CURSOR_STATE == CURSOR_ON_NO_BLINK)
        LCD_SendCommand(LCD_DISPLAY_ON_CURSOR_ON_BLINKING_OFF);
    #endif

    /*  Clear Screen    */
    LCD_SendCommand(LCD_CLEAR_DISPLAY);
}



void LCD_SendCommand(uint8 Instruction_value)
{
    /*  To send instruction command first thing write LOW to RS     */
    GPIO_WritePin(LCD_RS_PORT_ID,LCD_RS_PIN_ID,LOGIC_LOW);
    /*  I need to write data to lCD*/
    GPIO_WritePin(LCD_RW_PORT_ID,LCD_RW_PIN_ID,LOGIC_LOW);

    _delay_ms(1); /* delay for processing Tas = 50ns */

    /*  Write high to E pin in LCD to read data that will send  */
    GPIO_WritePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_HIGH);

    _delay_ms(1); /* delay for processing Tpw - Tdws = 190ns */

    /*send data depend on wires 4 OR 8  */
    #if (LCD_BITS_MODE == LCD_8_BIT_MODE)
        /*  Send data direct though DB0 : DB7   */
        GPIO_WritePort(LCD_DATA_PORT,Instruction_value);
        _delay_ms(1); /* delay for processing Tdsw = 100ns */
    #elif (LCD_BITS_MODE == LCD_4_BIT_MODE)
        /*  Note⛔🙆‍♂️👀 Here Most send MS 4Bits  First */
        uint8 First_4_bit = (Instruction_value >> 4) ;
        for(uint8 it =0 ; it < 4 ;it++ )
        {
            GPIO_WritePin(LCD_DATA_PORT,LCD_4_BIT_START_PIN + it,( (First_4_bit >> it) & (0x01) ) );
        }
        _delay_ms(1); /* delay for processing Tdsw = 100ns */
         /*  Write Low to E pin in LCD to there is data in pins I wnat to read  as here read Most significant of Instruction*/
        GPIO_WritePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW);
        _delay_ms(1); /* delay for processing Th = 13ns */

        /*  Write high to E pin in LCD to read data that will send  */
        GPIO_WritePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_HIGH);
        _delay_ms(1); /* delay for processing Tpw - Tdws = 190ns */

        /*  Handle LS 4Bits to send     */
        First_4_bit = Instruction_value & 0x0F ;
        /*  Send  last 4 Bit of data    */
        for(uint8 it =0 ; it < 4 ;it++ )
        {
            GPIO_WritePin(LCD_DATA_PORT,LCD_4_BIT_START_PIN + it,( (First_4_bit >> it) & (0x01) ) );
        }
        _delay_ms(1); /* delay for processing Tdsw = 100ns */
    #endif

    /*  Write Low to E pin in LCD to there is data in pins I wnat to read  */
    GPIO_WritePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW);
    _delay_ms(1); /* delay for processing Th = 13ns */
}



void LCD_DisplayCharacter(uint8 char_value)
{
    /*  Here I want to display data in LCD so will write high in RS */
    GPIO_WritePin(LCD_RS_PORT_ID,LCD_RS_PIN_ID,LOGIC_HIGH);
    /*  As I want to write data to DDRAM to display in LCD  */
    GPIO_WritePin(LCD_RW_PORT_ID,LCD_RW_PIN_ID,LOGIC_LOW);

    _delay_ms(1); /* delay for processing Tas = 50ns */

    /*  Write high to E pin in LCD to read data that will send  */
    GPIO_WritePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_HIGH);

    _delay_ms(1); /* delay for processing Tpw - Tdws = 190ns */
    /*send data depend on wires 4 OR 8  */
    #if (LCD_BITS_MODE == LCD_8_BIT_MODE)
        /*  Send data direct though DB0 : DB7   */
        GPIO_WritePort(LCD_DATA_PORT,char_value);
        _delay_ms(1); /* delay for processing Tdsw = 100ns */
    #elif (LCD_BITS_MODE == LCD_4_BIT_MODE)
        /*  Note⛔🙆‍♂️👀 Here Most send MS 4Bits  First */
        uint8 First_4_bit = (char_value >> 4) ;
        for(uint8 it =0 ; it < 4 ;it++ )
        {
            GPIO_WritePin(LCD_DATA_PORT,LCD_4_BIT_START_PIN + it,( (First_4_bit >> it) & (0x01) ) );
        }
        _delay_ms(1); /* delay for processing Tdsw = 100ns */
         /*  Write Low to E pin in LCD to there is data in pins I wnat to read  as here read Most significant of Instruction*/
        GPIO_WritePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW);
        _delay_ms(1); /* delay for processing Th = 13ns */

        /*  Write high to E pin in LCD to read data that will send  */
        GPIO_WritePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_HIGH);
        _delay_ms(1); /* delay for processing Tpw - Tdws = 190ns */

        /*  Handle LS 4Bits to send     */
        First_4_bit = char_value & 0x0F ;
        /*  Send  last 4 Bit of data    */
        for(uint8 it =0 ; it < 4 ;it++ )
        {
            GPIO_WritePin(LCD_DATA_PORT,LCD_4_BIT_START_PIN + it,( (First_4_bit >> it) & (0x01) ) );
        }
        _delay_ms(1); /* delay for processing Tdsw = 100ns */
    #endif
    /*  Write Low to E pin in LCD to there is data in pins I wnat to read  */
    GPIO_WritePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW);
    _delay_ms(1); /* delay for processing Th = 13ns */

    col_global++;
    if(col_global == 16)
    {
        row_global = 1 ;
        col_global = 0 ;
    }
}



void LCD_DisplayString(const uint8 * str_content)
{
    uint8 it = 0 ;
    while(str_content[it] != '\0')
    {
        LCD_DisplayCharacter(str_content[it]);
        it++;
    }
}


void LCD_MoveCursor(uint8 row , uint8 col)
{
    uint8 New_Location ;
    /*  calculate location that cursor will move to     */
    switch(row)
    {
        case 0 : 
            New_Location = col ;
            col_global = col ;
            row_global = 0 ;
            break ;
        
        case 1 :
            New_Location = col + 0x40 ;
            col_global = col ;
            row_global = 1 ;
            break;

        case 2 :
            New_Location = col + 0x10 ;
            break;

        case 3 : 
            New_Location = col + 0x50 ;
            break;
        default :
            break ;
    }
    /*  Call function to take palce of this command     */
    LCD_SendCommand(LCD_SET_CURSOR_LOCATION | New_Location);
}


void LCD_DisplayStringRowCol(const uint8 * str_content , uint8 row , uint8 col)
{
    LCD_MoveCursor(row,col);
    LCD_DisplayString(str_content);
}

void LCD_ClearScreen(void)
{
    col_global = 0 , row_global = 0;
    LCD_SendCommand(LCD_CLEAR_DISPLAY);
}



void LCD_MoveCursorRight(void)
{
    
    if(col_global == 15 && row_global == 0 )
    {
        col_global = 0 , row_global = 1 ;
        LCD_MoveCursor(row_global,col_global);
    }
    else if (col_global == 15 && row_global == 1 )
    {
        col_global = 0 , row_global = 0 ;
        LCD_MoveCursor(row_global,col_global);
    }
    else{ // safe shift right no problem
        LCD_SendCommand(LCD_CURSOR_MOVE_RIGHT);
        col_global++;
    }
}


void LCD_MoveCursorLeft(void)
{
    if(col_global == 0 && row_global == 0)
    {
        col_global = 15 , row_global = 1 ;
        LCD_MoveCursor(row_global,col_global);
    }
    else if (col_global == 0 && row_global == 1)
    {
        col_global = 15 , row_global = 0 ;
        LCD_MoveCursor(row_global,col_global);
    }
    else
    {
        LCD_SendCommand(LCD_CURSOR_MOVE_LEFT);
        col_global--;
    }
    
}


void LCD_ShitEntireDisplayRight(void)
{
    LCD_SendCommand(LCD_ENTIRE_DISPLAY_RIGHT);
}

void LCD_ShitEntireDisplayLeft(void)
{
    LCD_SendCommand(LCD_ENTIRE_DISPLAY_LEFT);
}


void LCD_GenerateCharacterCGRAM(const uint8 * Custom_character , uint8 location)
{
    LCD_SendCommand(LCD_CGRAM_LOCATION + (location * 8) );
    for(uint8 it = 0 ; it < 8 ;it++)
    {
        LCD_DisplayCharacter(Custom_character[it]);
    }
}


void LCD_DisplayCustomCharacter(uint8 location)
{
    LCD_DisplayCharacter(location);
}

void LCD_DisplayCustomCharacterRowCol(uint8 location , uint8 row ,uint8 col)
{
    LCD_MoveCursor(row,col);
    LCD_DisplayCharacter(location);
}




void LCD_intToString(uint32 data)
{
	 uint8 string_buff[17];// I write char not sint8_t(signed char ) to avoid warning
	 itoa(data , string_buff , 10); /* Use itoa C function to convert the data to its corresponding ASCII value, 10 for decimal */
	 LCD_DisplayString( (uint8_t *)string_buff);
}
