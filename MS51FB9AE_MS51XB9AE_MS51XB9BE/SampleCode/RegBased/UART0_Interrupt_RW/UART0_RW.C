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

/***********************************************************************************************************/
//  File Function: MS51 UART0 receive and transmit loop test
/***********************************************************************************************************/
#include "MS51_16K_IAR.h"

unsigned char uart_receive_data;

/*
struct U1BitFlag
{   unsigned char receiveFlag: 1;
    unsigned char bufOverFlag: 1;
}U1Flag;
*/


/*************************************************************/
/*  UART interrupt subroutine.                               */
/**************************************************************/
/*#pragma vector=0x23
__interrupt void UART0_ISR(void){
    if (RI)
    {   
      Flag.receiveFlag = 1;
      uart_receive_data = SBUF;
      clr_SCON_RI;                                         // Clear RI (Receive Interrupt).
    }
    if (TI)
    {       
        clr_SCON_TI;                                       // Clear TI (Transmit Interrupt).
    }

}

*/

void main(void)
{
  
/* Initial UART0 */
    P06_PUSHPULL_MODE;
    P07_INPUT_MODE;
    UART_Open(24000000,UART0_Timer3,115200);                 /*condition is: Fsys, UART0 or UART1 , Baudrate  */
    ENABLE_UART0_PRINTF;

    ENABLE_UART0_INTERRUPT;                                  /* Enable UART0 interrupt */
    ENABLE_GLOBAL_INTERRUPT;                                 /* Global interrupt enable */
  
/* while receive data from RXD, send this data to TXD */
  while(1)
  {
    if (uart0_receive_flag)
    {
      uart0_receive_flag = 0;
      clr_IE_ES;
      UART_Send_Data(UART0,uart_receive_data);
      set_IE_ES;
    }
  }
}