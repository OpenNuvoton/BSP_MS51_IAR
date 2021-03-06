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
//  File Function: ML51 UART1 interrupt demo
//***********************************************************************************************************
#include "MS51_8K_IAR.h"

unsigned char  UART_BUFFER,BitFlag;
void main (void)
{
    P17_PUSHPULL_MODE;                      // For I/O toggle display
/* Modify HIRC to 24MHz for UART baud rate deviation not over 1%*/
    MODIFY_HIRC_24();
    UART_Open(24000000,UART1_Timer3,115200);
    ENABLE_UART1_INTERRUPT;                 //For interrupt enable , interrupt subroutine is in uart.c file
    ENABLE_GLOBAL_INTERRUPT;                //ENABLE_GLOBAL_INTERRUPT

    while(1)
    {
      if (uart1_receive_flag)
      {
          P17 = ~ P17;      //Receive each byte P12 toggle, never work under debug mode
          UART_Send_Data(UART1,uart1_receive_data);
          uart1_receive_flag = 0;
      }
    }
}
  
