/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2019 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

//***********************************************************************************************************
//  Website: http://www.nuvoton.com
//  E-Mail : MicroC-8bit@nuvoton.com
//  Date   : Jan/21/2019
//***********************************************************************************************************

//***********************************************************************************************************
//  File Function: MS51 UART1 interrupt demo
//***********************************************************************************************************
#include "MS51_16K_IAR.h"

unsigned char  UART_BUFFER,MBitFlag;
struct MBitFlag
{
        unsigned char riflag: 1;
}MFlag;



/****************************************************************************************************************
 * FUNCTION_PURPOSE: Main function 
  
 !!! MS51 UART1 pin also occupied by debug pin, 
 please remove Nu-link or not in debug mode to test UART1 function.

 External UART1 connect also disturb debug download

 ***************************************************************************************************************/
void main (void)
{
    ALL_GPIO_QUASI_MODE;
    P12_PUSHPULL_MODE;    // For I/O toggle display
/* Modify HIRC to 24MHz for UART baud rate deviation not over 1%*/
    MODIFY_HIRC_24();
    UART_Open(24000000,UART1_Timer3,115200);
    ENABLE_UART1_INTERRUPT;                 //For interrupt enable
    ENABLE_GLOBAL_INTERRUPT;                //ENABLE_GLOBAL_INTERRUPT

    while(1)
    {
      if (MFlag.riflag)
      {
          P12 = ~ P12;      //Receive each byte P12 toggle, never work under debug mode
          DISABLE_UART1_INTERRUPT;
          UART_Send_Data(UART1,UART_BUFFER);
          MFlag.riflag = 0;
          ENABLE_UART1_INTERRUPT;
      }
    }
}
  
