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
#include "MS51_32K_IAR.h"

unsigned char temp=0x30;
unsigned char  UART_BUFFER,BitFlag;

void main (void)
{
    UART2_Open(16000000,115200);                 /* Open UART2 use timer1 as baudrate generate and baud rate = 115200*/
    P03_QUASI_MODE;                              /* Set UART2_TXD pin P0.3 as Quasi mode */
    P04_INPUT_MODE;                              /* Set UART2_RXD pin P0.4 as Input mode */
    ENABLE_UART2_TXD_P03;
    ENABLE_UART2_RXD_P04;
    ENABLE_SC0_RECEIVE_DATA_REACH_INTERRUPT;
    ENABLE_GLOBAL_INTERRUPT;

/* while receive data from RXD, send this data to TXD */
  while(1)
  {
    if (uart2rvflag)
    {
      uart2rvflag = 0;
      UART2_Send_Data(uart2rvbuffer);
    }
  }

}
  
